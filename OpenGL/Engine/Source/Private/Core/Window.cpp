#include "PCH.h"
#include "Window.h"
#include "Engine.h"
#include "InputSystem.h"

Window::Window(const ObjectInitData& _data) : Object(_data)
{
	GetEngine()->RegisterWindow(this);
}

Window::~Window()
{
	GetEngine()->WindowDestroyed(this);
}

void Window::CreateWindowClass(Object* _outer, const char* _name)
{
	WNDCLASSEX windowClass; //window class

	/*Fill out the window class structure*/
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = HandleMsgSetup;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = _outer->GetEngine()->GetHandleInstance();
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = _name;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	/*      Register window class*/
	if (!RegisterClassEx(&windowClass))
	{
		throw "Failed to register window class";
	}
}

void Window::RegisterScene(Scene* _scene)
{
	m_scene = _scene;
}

void Window::SpawnWindowInternal(const NewWindowParams& _params)
{
	RECT windowRect;

	/*Screen/display attributes*/
	int width = _params.width;
	int height = _params.height;
	int bits = 32;

	windowRect.left = (long)0;					//set left value to 0
	windowRect.right = (long)width;				//set right value to requested width
	windowRect.top = (long)0;					//set top value to 0
	windowRect.bottom = (long)height;			//set bottom value to requested height

	CreateWindowEx(NULL,
		_params.windowClass,					//class name
		"OpenGL Robot",							//app name
		WS_OVERLAPPEDWINDOW |
		WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		_params.x, _params.y,					//x and y coords
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,		//width, height
		NULL,									//handle to parent
		NULL,									//handle to menu
		GetEngine()->GetHandleInstance(),		//application instance
		this);									//no xtra params

	ShowWindow(m_handle, SW_SHOWDEFAULT);
	UpdateWindow(m_handle);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

bool Window::SetupPixelFormat()
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
			1,                                      //default version
			PFD_DRAW_TO_WINDOW |                    //window drawing support
			PFD_SUPPORT_OPENGL |                    //opengl support
			PFD_DOUBLEBUFFER,                       //double buffering support
			PFD_TYPE_RGBA,                          //RGBA color mode
			32,                                     //32 bit color mode
			0, 0, 0, 0, 0, 0,                       //ignore color bits
			0,                                      //no alpha buffer
			0,                                      //ignore shift bit
			0,                                      //no accumulation buffer
			0, 0, 0, 0,                             //ignore accumulation bits
			16,                                     //16 bit z-buffer size
			0,                                      //no stencil buffer
			0,                                      //no aux buffer
			PFD_MAIN_PLANE,                         //main drawing plane
			0,                                      //reserved
			0, 0, 0 };                              //layer masks ignored

			/*      Choose best matching format*/
	nPixelFormat = ChoosePixelFormat(m_deviceContext, &pfd);

	/*      Set the pixel format to the device context*/
	SetPixelFormat(m_deviceContext, nPixelFormat, &pfd);

	return true;
}

void Window::SetupPalette()
{

}

bool Window::Update()
{
	MSG msg;
	while (PeekMessageA(&msg, m_handle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		std::cout << msg.message << std::endl;
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}

	Render();
	
	return true;
}

void Window::MsgCreate()
{
	m_deviceContext = GetDC(m_handle);
	SetupPixelFormat();

	m_glRenderingContext = wglCreateContext(m_deviceContext);
	wglMakeCurrent(m_deviceContext, m_glRenderingContext);

	gladLoadGL();

	AddMenus();
}

void Window::MsgRepaint()
{

}

void Window::AddMenus()
{

}

void Window::Render()
{
	wglMakeCurrent(m_deviceContext, m_glRenderingContext);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GetEngine()->RenderScene(m_scene);

	SwapBuffers(m_deviceContext);
}

//Call for when something happens in the window
LRESULT Window::HandleMsg(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
	case WM_CREATE:
		m_handle = _hWnd;
		MsgCreate();
		break;

	case WM_PAINT:
		MsgRepaint();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_KEYDOWN:
		m_scene->GetInputSystem()->KeyPressed(static_cast<unsigned char>(_wParam));
		break;

	case WM_KEYUP:
		m_scene->GetInputSystem()->KeyReleased(static_cast<unsigned char>(_wParam));
		break;

	case WM_MOUSEMOVE:
		m_scene->GetInputSystem()->MouseMoved(GET_X_LPARAM(_lParam), GET_Y_LPARAM(_lParam));
		break;

	case WM_LBUTTONDOWN:
		m_scene->GetInputSystem()->MouseButtonPressed(0);
		break;

	case WM_MBUTTONDOWN:
		m_scene->GetInputSystem()->MouseButtonPressed(1);
		break;

	case WM_RBUTTONDOWN:
		m_scene->GetInputSystem()->MouseButtonPressed(2);
		break;

	case WM_LBUTTONUP:
		m_scene->GetInputSystem()->MouseButtonReleased(0);
		break;

	case WM_MBUTTONUP:
		m_scene->GetInputSystem()->MouseButtonReleased(1);
		break;

	case WM_RBUTTONUP:
		m_scene->GetInputSystem()->MouseButtonReleased(2);
		break;
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (_msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(_lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		// sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(_hWnd, _msg, _wParam, _lParam);
	}

	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));

	// forward message to window class handler
	return pWnd->HandleMsg(_hWnd, _msg, _wParam, _lParam);
}

void Window::SetAsMainWindow()
{
	GetEngine()->SetMainWindow(this);
}

HWND Window::GetHandle() const
{
	return m_handle;
}

unsigned int Window::GetWidth() const
{
	return m_width;
}

unsigned int Window::GetHeight() const
{
	return m_height;
}

float Window::GetAspectRatio() const
{
	return m_width / m_height;
}