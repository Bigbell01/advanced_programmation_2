#include "stdafx.h"
#include "resource.h"

#include "Engine.h"
#include "Sprite.h"
#include "TestEnvironment.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE prevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	srand((unsigned int)time(0));

	Engine::GetInstance()->Init(hInstance, nCmdShow, 720, 504);

	TestEnvironment* game = new TestEnvironment();

	int assert = Engine::GetInstance()->Run();

	delete game;

	Engine::Kill();

	return assert;
}