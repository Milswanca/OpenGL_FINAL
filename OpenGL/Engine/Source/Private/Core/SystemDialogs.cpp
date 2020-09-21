#include "PCH.h"
#include "SystemDialogs.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

void SystemDialogs::OpenFile()
{
	char szFile[MAX_PATH];

	// open a file name
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	// Now simpley display the file name 
	MessageBox(NULL, ofn.lpstrFile, "File Name", MB_OK);
	return;
}