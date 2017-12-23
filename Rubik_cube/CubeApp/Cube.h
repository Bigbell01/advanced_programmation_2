#pragma once

#include "D3DApp.h"
#include "D3DUtils.h"
#include "Vertex.h"

class Cube
{
public:
	Cube();
	Cube(int color1, int color2, int color3, int color4, int color5, int color6);
	~Cube();

	void CreateVertices(int color1, int color2, int color3, int color4, int color5, int color6);
	void CreateIndices();

	D3DXMATRIX GetWorld() { return T *Ry; }

	bool PositionGet() { return hasSetPosition; }
	void PositionSet(bool hasSet) { hasSetPosition = hasSet; }

	void SetPosition(float x, float y, float z) 
	{ 
		D3DXMatrixTranslation(&T, x *1.1f, y*1.1f, z*1.1f);
	}

	void SetRotation(D3DXVECTOR3& axis, float rotation) 
	{ 
		D3DXMatrixRotationAxis(&Ry, &axis, rotation); 
	}

	void Draw();

private:
	/*const int GREEN = 0x0000FF00;
	const int RED = 0x0000FF0000;
	const int BLUE = 0x0000000066;
	const int YELLOW = 0x0000FFFF00;
	const int WHITE = 0x0000FFFFFF;
	const int ORANGE = 0x0000FF8300;*/

	//int color1;
	//int color2; 
	//int color3;
	//int color4;
	//int color5;
	//int color6;

	bool hasSetPosition;

	D3DXMATRIX Ry;
	D3DXMATRIX T;

	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;
};

