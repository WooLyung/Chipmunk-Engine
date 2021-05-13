#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1.h>
#include <windows.h>

class ChmWindow
{
private:
	void RegisterWNDCLASS(HINSTANCE);
	HWND CreateWindowFunc(HINSTANCE, int);

	HINSTANCE hInstance;
	int nCmdShow;
	HWND hWnd;

public:
	ChmWindow(HINSTANCE, int);

	HWND GetHWND();
};