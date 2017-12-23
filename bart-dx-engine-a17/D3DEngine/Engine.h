#pragma once

#include "D3DApp.h"
#include "Resources.h"
#include "Input.h"
#include "Timer.h"
#include "Component.h"
#include "Camera.h"

#define gEngine Engine::GetInstance()
#define gCamera gEngine->GetCamera()
#define gResources gEngine->GetResources()
#define gInput gEngine->GetInput()
#define gGameTimer gEngine->GetGameTimer()
#define gDT gGameTimer->GetDeltaTime()
class Engine
	: public D3DApp
{
#pragma region SINGLETON
public:

	static Engine* GetInstance()
	{
		if (!instance)
		{
			instance = new Engine();
		}
		return instance;
	}

	static void Kill()
	{
		delete instance;
		instance = 0;
	}

	int GenerateRandNumb(const int number)
	{
		//Generate a number between 0(inclusive) and your number(excluded)
		int RandomNumber = rand() % number;

		return RandomNumber;
	}

private:
	Engine();
	~Engine();

	static Engine* instance;
#pragma endregion

public:
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	Camera* GetCamera() { return camera; }
	void SetColor(UINT8 r, UINT8 g, UINT8 b) { this->r = r; this->g = g; this->b = b; }
	void SetCameraPosition(D3DXVECTOR3 position) { camera->GetTransform()->SetPosition(position); }
	void SetCamera(Camera* cam) { camera = cam; }
	Resources* GetResources() { return resources; }
	Input* GetInput() { return input; }
	Timer* GetGameTimer() { return gameTimer; }

	virtual void Init(HINSTANCE hInstance, int nCmdShow);
	virtual void Init(HINSTANCE hInstance, int nCmdShow, int width, int height);

	void Update();
	void Draw();

private:
	UINT8 r, g, b;
	float width, height;
	Resources* resources;
	Input* input;
	Timer* gameTimer;
	Camera* camera;
	ID3DXSprite* spriteBatch;
};

