#include "ChmRenderManager.h"

void ChmRenderManager::CreateRenderTarget(ID2D1Factory* pFactory, HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &renderTarget);

	this->renderTarget = renderTarget;
}

ID2D1HwndRenderTarget* ChmRenderManager::GetRenderTarget()
{
	return renderTarget;
}

void ChmRenderManager::Init(ID2D1Factory* pFactory, HWND hWnd)
{
	CreateRenderTarget(pFactory, hWnd);
}

ChmRenderManager::~ChmRenderManager()
{
	delete renderTarget;
}