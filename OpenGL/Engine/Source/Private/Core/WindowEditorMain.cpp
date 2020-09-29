#include "PCH.h"
#include "WindowEditorMain.h"
#include "SystemDialogs.h"
#include "AssetImporter.h"

#define IDM_FILE_IMPORT 1

WindowEditorMain::WindowEditorMain(const ObjectInitData& _data) : Window(_data)
{

}

void WindowEditorMain::AddMenus()
{
	HMENU assetMenuBar;
	HMENU hMenu;

	assetMenuBar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_FILE_IMPORT, L"&Import");

	AppendMenuW(assetMenuBar, MF_POPUP, (UINT_PTR)hMenu, L"&Assets");
	SetMenu(GetHandle(), assetMenuBar);
}

void WindowEditorMain::ImportFilePressed()
{
	std::string open = SystemDialogs::OpenFile("All\0*.*\0Text\0*.TXT\0");
	std::string save = SystemDialogs::SaveFile("All\0*.*\0Text\0*.TXT\0");
	AssetImporter::ImportAsset(open, save);
	MessageBox(GetHandle(), "Finished Importing Asset", "Success", MB_OK);
}

LRESULT WindowEditorMain::HandleMsg(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	LRESULT ret = Window::HandleMsg(_hWnd, _msg, _wParam, _lParam);

	switch (_msg)
	{
	case WM_COMMAND:
		switch (LOWORD(_wParam))
		{
		case IDM_FILE_IMPORT:
			ImportFilePressed();
			break;
		}
		break;
	}

	return ret;
}
