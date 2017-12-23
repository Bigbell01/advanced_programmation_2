#pragma once

#include "D3DApp.h"
#include "Vertex.h"
#include <vector>

#include "Cube.h"

class CubeApp
	: public D3DApp
{

public:
	CubeApp();
	CubeApp(HINSTANCE hInstance, int nCmdShow);
	~CubeApp();

	void Update();
	void Draw();

private:
	float currRot;

	std::vector<Cube*> cubeList;

	ID3DXEffect* mFx;
	ID3DXBuffer* mErrors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;
	D3DXHANDLE mhEyePos;
	D3DXHANDLE mhFogColor;
	D3DXHANDLE mhFogStart;
	D3DXHANDLE mhFogRange;

	Cube* cube1;
	Cube* cube2;
	Cube* cube3;

	Cube* cube4;
	Cube* cube5;
	Cube* cube6;

	Cube* cube7;
	Cube* cube8;
	Cube* cube9;

	Cube* cube10;
	Cube* cube11;
	Cube* cube12;

	Cube* cube13;
	Cube* cube14;
	Cube* cube15;

	Cube* cube16;
	Cube* cube17;
	Cube* cube18;

	Cube* cube19;
	Cube* cube20;
	Cube* cube21;

	Cube* cube22;
	Cube* cube23;
	Cube* cube24;

	Cube* cube25;
	Cube* cube26;
	Cube* cube27;

	const int GREEN = 0x0000FF00;
	const int RED = 0x0000FF0000;
	const int BLUE = 0x0000000066;
	const int YELLOW = 0x0000FFFF00;
	const int WHITE = 0x0000FFFFFF;
	const int ORANGE = 0x0000FF8300;
	const int BLACK = 0x00000e1111;

	// Camera		
	D3DXMATRIX view;
	D3DXMATRIX proj;
	
	D3DXVECTOR3 eyePos;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;
};