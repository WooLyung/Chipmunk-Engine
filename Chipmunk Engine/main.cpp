#include "ChmEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	ChmEngine* engine = new ChmEngine();
	engine->Init(hInstance, nCmdShow);
	int result = engine->Start();

	return result;
}