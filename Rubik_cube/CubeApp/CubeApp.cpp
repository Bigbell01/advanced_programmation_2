#include "stdafx.h"
#include "CubeApp.h"

CubeApp::CubeApp()
{
}

CubeApp::CubeApp(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
	, currRot(0.f)
	, eyePos(0.f, 6.f, -10.f)
	, target(0.f, -1.f, 0.f)
	, up(0.f, 1.0f, 0.f)
{
	CreateAllVertexDeclaration();

	HR(D3DXCreateEffectFromFileW(
		gD3DDevice, L"Transform.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mFx, &mErrors));

	if (mErrors)
	{
		MessageBoxW(0, (LPCWSTR)mErrors->GetBufferPointer(), 0, 0);
	}

	mhTech = mFx->GetTechniqueByName("FogTech");
	mFx->SetTechnique(mhTech);

	mhWVP = mFx->GetParameterByName(0, "gWVP");
	mhEyePos = mFx->GetParameterByName(0, "gEyePos");
	mhFogColor = mFx->GetParameterByName(0, "gFogColor");
	mhFogStart = mFx->GetParameterByName(0, "gFogStart");
	mhFogRange = mFx->GetParameterByName(0, "gFogRange");

	HR(mFx->SetVector(mhFogColor, &D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f)));
	HR(mFx->SetFloat(mhFogStart, 5.0f));
	HR(mFx->SetFloat(mhFogRange, 25.0f));

	D3DXMatrixLookAtRH(&view, &eyePos, &target, &up);
	D3DXMatrixPerspectiveFovRH(&proj, D3DX_PI / 4,
		(float)d3dPP.BackBufferWidth / (float)d3dPP.BackBufferHeight, 0.01f, 1000.0f);

	cubeList.push_back(cube1 = new Cube(BLACK, RED, BLUE, BLACK, WHITE, BLACK));
	cubeList.push_back(cube2 = new Cube(BLACK, BLACK, BLUE, BLACK, WHITE, BLACK));
	cubeList.push_back(cube3 = new Cube(GREEN, BLACK, BLUE, BLACK, WHITE, BLACK));

	cubeList.push_back(cube4 = new Cube(BLACK, RED, BLUE, BLACK, BLACK, BLACK));
	cubeList.push_back(cube5 = new Cube(BLACK, BLACK, BLUE, BLACK, BLACK, BLACK));
	cubeList.push_back(cube6 = new Cube(GREEN, BLACK, BLUE, BLACK, BLACK, BLACK));

	cubeList.push_back(cube7 = new Cube(BLACK, RED, BLUE, BLACK, BLACK, ORANGE));
	cubeList.push_back(cube8 = new Cube(BLACK, BLACK, BLUE, BLACK, BLACK, ORANGE));
	cubeList.push_back(cube9 = new Cube(GREEN, BLACK, BLUE, BLACK, BLACK, ORANGE));

	cubeList.push_back(cube10 = new Cube(BLACK, RED, BLACK, BLACK, WHITE, BLACK));
	cubeList.push_back(cube11 = new Cube(BLACK, BLACK, BLACK, BLACK, WHITE, BLACK));
	cubeList.push_back(cube12 = new Cube(GREEN, BLACK, BLACK, BLACK, WHITE, BLACK));

	cubeList.push_back(cube13 = new Cube(BLACK, RED, BLACK, BLACK, BLACK, BLACK));
	cubeList.push_back(cube14 = new Cube(BLACK, BLACK, BLACK, BLACK, BLACK, BLACK));
	cubeList.push_back(cube15 = new Cube(GREEN, BLACK, BLACK, BLACK, BLACK, BLACK));

	cubeList.push_back(cube16 = new Cube(BLACK, RED, BLACK, BLACK, BLACK, ORANGE));
	cubeList.push_back(cube17 = new Cube(BLACK, BLACK, BLACK, BLACK, BLACK,ORANGE));
	cubeList.push_back(cube18 = new Cube(GREEN, BLACK, BLACK, BLACK, BLACK,ORANGE));

	cubeList.push_back(cube19 = new Cube(BLACK,RED, BLACK,YELLOW,WHITE, BLACK));
	cubeList.push_back(cube20 = new Cube(BLACK, BLACK, BLACK,YELLOW,WHITE, BLACK));
	cubeList.push_back(cube21 = new Cube(GREEN, BLACK, BLACK,YELLOW,WHITE, BLACK));
										 
	cubeList.push_back(cube22 = new Cube(BLACK,RED, BLACK,YELLOW, BLACK, BLACK));
	cubeList.push_back(cube23 = new Cube(BLACK, BLACK, BLACK,YELLOW, BLACK, BLACK));
	cubeList.push_back(cube24 = new Cube(GREEN, BLACK, BLACK,YELLOW, BLACK, BLACK));
										
	cubeList.push_back(cube25 = new Cube(BLACK,RED, BLACK, YELLOW, BLACK,ORANGE));
	cubeList.push_back(cube26 = new Cube(BLACK,BLACK, BLACK,YELLOW,BLACK,ORANGE));
	cubeList.push_back(cube27 = new Cube(GREEN,BLACK, BLACK,YELLOW,BLACK,ORANGE));
	
	for(int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (Cube* cube : cubeList)
				{
					if (!cube->PositionGet())
					{
						cube->SetPosition(i, j, k);
						cube->PositionSet(true);
					}
					else
					{
						continue;
					}
					break;
				}
			}
		}
	}	
}

CubeApp::~CubeApp()
{
	DestroyAllDeclaration();
}

void CubeApp::Update()
{
	currRot += 0.0001f;

	for (Cube* cube : cubeList)
	{
		cube->SetRotation(D3DXVECTOR3(1.0f, 1.0f, 0.0f), currRot);
	}
}

void CubeApp::Draw()
{
	HR(gD3DDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128,128, 128), 1.0f, 0));

	HR(mFx->SetValue(mhEyePos, &eyePos, sizeof(D3DXVECTOR3)));
	
	D3DXMATRIX WVP;
	D3DXMatrixIdentity(&WVP);

	// Draw 3D
	HR(gD3DDevice->BeginScene());

	UINT nbPass;
	HR(mFx->Begin(&nbPass, 0));

	for (int i = 0; i < nbPass; i++)
	{
		HR(mFx->BeginPass(i));

		for (Cube* cube : cubeList)
		{
			WVP = cube->GetWorld() * view * proj;
			mFx->SetMatrix(mhWVP, &WVP);
			mFx->CommitChanges();
			cube->Draw();
		}
		

		HR(mFx->EndPass());
	}

	HR(mFx->End());

	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}
