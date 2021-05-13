#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1.h>
#include <windows.h>

class ChmRenderManager
{
private:
	void CreateRenderTarget(ID2D1Factory*, HWND);

	ID2D1HwndRenderTarget* renderTarget;

public:
	~ChmRenderManager();

	void Init(ID2D1Factory*, HWND);

	ID2D1HwndRenderTarget* GetRenderTarget();
};