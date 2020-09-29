#pragma once
#include "Window.h"

class WindowEditorMain : public Window
{
public:
	WindowEditorMain(const ObjectInitData& _data);

	virtual void AddMenus() override;

protected:
	virtual LRESULT HandleMsg(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) override;

private:
	void ImportFilePressed();
};

