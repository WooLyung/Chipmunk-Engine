#include "ChmWindow.h"
#include "ChmEngine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		ChmRenderManager* renderManager = ChmEngine::GetInstance()->GetRenderManager();
		if (renderManager)
		{
			ID2D1HwndRenderTarget* renderTarget = ChmEngine::GetInstance()->GetRenderManager()->GetRenderTarget();

			if (renderTarget)
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				renderTarget->Resize(D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top));
			}
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

ChmWindow::ChmWindow(HINSTANCE hInstance, int nCmdShow)
{
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;

	RegisterWNDCLASS(hInstance);
	this->hWnd = CreateWindowFunc(hInstance, nCmdShow);
}

void ChmWindow::RegisterWNDCLASS(HINSTANCE hInstance)
{
	WNDCLASS wc;

	wc.style = NULL;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = WHITE_BRUSH;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"chipmunk engine class";
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);
}

HWND ChmWindow::CreateWindowFunc(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd = CreateWindow(L"chipmunk engine class", L"chipmunk engine window", WS_OVERLAPPEDWINDOW,
		100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

HWND ChmWindow::GetHWND()
{
	return hWnd;
}