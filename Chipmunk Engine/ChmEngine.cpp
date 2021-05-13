#include "ChmEngine.h"

ChmEngine* ChmEngine::instance = nullptr;

void ChmEngine::CreateFactory()
{
	ID2D1Factory* pFactory = nullptr;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	this->pFactory = pFactory;
}

void ChmEngine::Init(HINSTANCE hInstance, int nCmdShow)
{
	CreateFactory();

	window = new ChmWindow(hInstance, nCmdShow);

	renderManager = new ChmRenderManager();
	renderManager->Init(pFactory, window->GetHWND());
}

int ChmEngine::Loop()
{
	ID2D1HwndRenderTarget* renderTarget = renderManager->GetRenderTarget();
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

		Update(renderTarget);
	}
	return msg.wParam;
}

int ChmEngine::Start()
{
	return Loop();
}

void ChmEngine::Update(ID2D1HwndRenderTarget* renderTarget)
{
	renderTarget->BeginDraw();
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	ID2D1SolidColorBrush* brush = nullptr;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &brush);
	renderTarget->DrawRectangle(D2D1::RectF(20, 20, 60, 60), brush);

	brush->Release();
	renderTarget->EndDraw();
}

ChmEngine::ChmEngine()
{
	instance = this;
}

ChmEngine::~ChmEngine()
{
	delete renderManager;
	delete window;
	delete pFactory;
}

ChmEngine* ChmEngine::GetInstance()
{
	return instance;
}

ChmRenderManager* ChmEngine::GetRenderManager()
{
	return renderManager;
}

ChmWindow* ChmEngine::GetWindow()
{
	return window;
}