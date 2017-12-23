#include "stdafx.h"

#include "PeggleKevenBell.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	gEngine->Init(hInstance, nCmdShow, 1280, 720);

	PeggleKevenBell* game = new PeggleKevenBell();

	gEngine->Run();

	gEngine->Kill();
	return 0;
	
}
