#pragma comment(lib, "d2d1")
#include <d2d1.h>
#include <windows.h>

ID2D1HwndRenderTarget* renderTarget = nullptr;

ID2D1Factory* CreateFactory()
{
	ID2D1Factory* pFactory = nullptr;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	return pFactory;
}

ID2D1HwndRenderTarget* CreateRenderTarget(ID2D1Factory* pFactory, HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &renderTarget);

	return renderTarget;
}

void Update()
{
	renderTarget->BeginDraw();
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	ID2D1SolidColorBrush* brush = nullptr;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &brush);
	renderTarget->DrawRectangle(D2D1::RectF(20, 20, 60, 60), brush);

	brush->Release();
	renderTarget->EndDraw();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (renderTarget != nullptr)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);
			renderTarget->Resize(D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top));
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void RegisterWNDCLASS(HINSTANCE hInstance)
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
	wc.lpszClassName = L"test_class";
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);
}

HWND CreateWindowFunc(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd = CreateWindow(L"test_class", L"test window", WS_OVERLAPPEDWINDOW,
		100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

int MessageLoop(HWND hWnd)
{
	bool isDone = false;
	MSG msg;

	while (!isDone)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		Update();
	}
	return msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	RegisterWNDCLASS(hInstance);
	HWND hWnd = CreateWindowFunc(hInstance, nCmdShow);

	ID2D1Factory* pFactory = CreateFactory();
	ID2D1HwndRenderTarget* renderTarget = CreateRenderTarget(pFactory, hWnd);

	int result = MessageLoop(hWnd);

	return result;
}