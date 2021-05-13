#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1.h>
#include <windows.h>
#include "ChmRenderManager.h"
#include "ChmWindow.h"

class ChmEngine
{
private:
	void CreateFactory();
	void Update(ID2D1HwndRenderTarget*);
	int Loop();

	static ChmEngine* instance;
	ID2D1Factory* pFactory = nullptr;

	ChmRenderManager* renderManager = nullptr;
	ChmWindow* window = nullptr;

public:
	ChmEngine();
	~ChmEngine();

	static ChmEngine* GetInstance();
	void Init(HINSTANCE, int);
	int Start();

	ChmRenderManager* GetRenderManager();
	ChmWindow* GetWindow();
};