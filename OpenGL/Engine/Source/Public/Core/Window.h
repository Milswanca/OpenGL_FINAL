#pragma once
#include "Object.h"
#include "Engine.h"

struct NewWindowParams;

class Window : public Object
{
public:
	struct NewWindowParams
	{
	public:
		const char* windowClass;
		const char* title = "";
		unsigned int style = 0;
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int width = 0;
		unsigned int height = 0;
	};

public:
	Window(const ObjectInitData& _data);
	~Window();

	template<typename T>
	static T* Create(Object* _outer, const NewWindowParams& _params)
	{
		T* window = _outer->GetEngine()->NewObject<T>(_outer);

		Window* w = reinterpret_cast<Window*>(window);
		w->SpawnWindowInternal(_params);

		return window;
	}
	
	static void CreateWindowClass(Object* _outer, const char* _name);
	bool Update();
	void SetAsMainWindow();
	void RegisterScene(Scene* _scene);

	virtual void MsgCreate();
	virtual void MsgRepaint();

	virtual void AddMenus();
	virtual void Render();

	//Getters
	HWND GetHandle() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	float GetAspectRatio() const;

protected:
	virtual LRESULT HandleMsg(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

private:
	void SpawnWindowInternal(const NewWindowParams& _params);
	bool SetupPixelFormat();
	void SetupPalette();

	//Messages
	static LRESULT WINAPI HandleMsgSetup(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	//Props
	HWND m_handle;
	HDC m_deviceContext;
	HGLRC m_glRenderingContext;
	unsigned int m_width;
	unsigned int m_height;

	Scene* m_scene;
};