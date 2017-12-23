#include "Engine.h"
#include <time.h>

Engine* Engine::instance = 0;

Engine::Engine()
	: D3DApp()
	, spriteBatch(nullptr)
	, camera(nullptr)
	, r(128), g(128), b(128)
{
	//Random
	std::srand((unsigned int)time(0));
}

Engine::~Engine()
{
	ReleaseCOM(spriteBatch);

	delete camera;

	delete resources;
	delete input;
	delete gameTimer;
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow)
{
	Init(hInstance, nCmdShow, 800, 600);
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	D3DApp::Init(hInstance, nCmdShow, width, height);

	this->width = width;
	this->height = height;

	resources = new Resources();

	input = new Input(GetAppInstance(), GetMainWindow(),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	gameTimer = new Timer();

	// Need to reset to get the correct total game time when GetGameTime() is called.
	gameTimer->Start();
	gameTimer->Reset();

	HR(D3DXCreateSprite(gD3DDevice, &spriteBatch));

	camera = new Camera(d3dpp.BackBufferWidth, d3dpp.BackBufferHeight);
	camera->GetTransform()->SetPosition(0, 0, 10);
}

void Engine::Update()
{
	// Fixed pipeline
	{
		HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));
		HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
		//HR(gD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));

		// pour le Alpha
		//HR(gD3DDevice->SetRenderState(D3DRS_ALPHAREF, 10));
		//HR(gD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));
		//HR(gD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE));

		// alpha blend
		//HR(gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
		//HR(gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1));
		//HR(gD3DDevice->SetRenderState( , D3DBLEND_SRCALPHA));
		//HR(gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	}

	input->poll();
	gameTimer->Tick();

	for (Component* c : Component::components)
	{
		c->Update();
	}
}

void Engine::Draw()
{
	HR(gD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(r, g, b), 1.0f, 0));

	HR(gD3DDevice->BeginScene());

	HR(spriteBatch->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_DONOTMODIFY_RENDERSTATE));

	for (Component* c: Component::components)
	{
		c->Draw2D(spriteBatch);
	}

	HR(spriteBatch->End());

	for (Component* c : Component::components)
	{
		c->Draw3D(camera->GetView(), camera->GetProj());
	}
	
	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}

