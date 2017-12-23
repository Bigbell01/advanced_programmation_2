#include "stdafx.h"
#include "Cube.h"

//Cube::Cube()
//{
//	D3DXMatrixIdentity(&T);
//	D3DXMatrixIdentity(&Ry);
//	CreateVertices(color1,color2, color3, color4, color5, color6);
//	CreateIndices();
//}

Cube::Cube(int color1, int color2, int color3, int color4, int color5, int color6)
{
	D3DXMatrixIdentity(&T);
	D3DXMatrixIdentity(&Ry);
	CreateVertices(color1, color2, color3, color4, color5, color6);
	CreateIndices();
}

Cube::~Cube()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Cube::CreateVertices(int color1, int color2, int color3, int color4, int color5, int color6)
{
	// Build Vertex Buffer
	(gD3DDevice->CreateVertexBuffer(
		24 * sizeof(VertexPosCol), 0, 0, D3DPOOL_MANAGED, &mVB, 0));

	VertexPosCol* vertices;

	HR(mVB->Lock(0, 0, (void**)&vertices, 0));

	//V1______V4
	//|      /|
	//|    /  |
	//|  /    |
	//V2/______V3

	// Local de mes vertices
	//front
	vertices[0] = VertexPosCol(-0.5f, 0.5f, 0.f, color1);
	vertices[1] = VertexPosCol(-0.5f, -0.5f, 0.f, color1);
	vertices[2] = VertexPosCol(0.5f, -0.5f, 0.f, color1);
	vertices[3] = VertexPosCol(0.5f, 0.5f, 0.f, color1);
	//back
	vertices[4] = VertexPosCol(-0.5f, 0.5f, -1.f, color2);
	vertices[5] = VertexPosCol(-0.5f, -0.5f, -1.f, color2);
	vertices[6] = VertexPosCol(0.5f, -0.5f, -1.f, color2);
	vertices[7] = VertexPosCol(0.5f, 0.5f, -1.f, color2);

	//left
	vertices[8] = VertexPosCol(-0.5f, 0.5f, -1.f, color3);
	vertices[9] = VertexPosCol(-0.5f, -0.5f, -1.f, color3);
	vertices[10] = VertexPosCol(-0.5f, -0.5f, 0.f, color3);
	vertices[11] = VertexPosCol(-0.5f, 0.5f, 0.f, color3);

	//right
	vertices[12] = VertexPosCol(0.5f, 0.5f, 0.f, color4);
	vertices[13] = VertexPosCol(0.5f, -0.5f, 0.f, color4);
	vertices[14] = VertexPosCol(0.5f, -0.5f, -1.f, color4);
	vertices[15] = VertexPosCol(0.5f, 0.5f, -1.f, color4);

	//top
	vertices[16] = VertexPosCol(-0.5f, -0.5f, 0.f, color5);
	vertices[17] = VertexPosCol(-0.5f, -0.5f, -1.f, color5);
	vertices[18] = VertexPosCol(0.5f, -0.5f, -1.f, color5);
	vertices[19] = VertexPosCol(0.5f, -0.5f, 0.f, color5);
	//bot
	vertices[20] = VertexPosCol(-0.5f, 0.5f, -1.f, color6);
	vertices[21] = VertexPosCol(-0.5f, 0.5f, 0.f, color6);
	vertices[22] = VertexPosCol(0.5f, 0.5f, 0.f, color6);
	vertices[23] = VertexPosCol(0.5f, 0.5f, -1.f, color6);

	HR(mVB->Unlock());
}

void Cube::CreateIndices()
{
	// Build Index Buffer
	HR(gD3DDevice->CreateIndexBuffer(
		36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	WORD* k;

	HR(mIB->Lock(0, 0, (void**)&k, 0));

	// Front face.
	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 0; k[4] = 2; k[5] = 3;
	
	// Back face.      
	k[6] = 4; k[7] = 6;  k[8] = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;
	
	// Left face.      
	k[12] = 8; k[13] = 9; k[14] = 10;
	k[15] = 8; k[16] = 10; k[17] = 11;
	
	// Right face.      
	k[18] = 12; k[19] = 13; k[20] = 14;
	k[21] = 12; k[22] = 14; k[23] = 15;
	
	// Top face.      
	k[24] = 16; k[25] = 17; k[26] = 18;
	k[27] = 16; k[28] = 18; k[29] = 19;
	
	// Bottom face    
	k[30] = 20; k[31] = 21; k[32] = 22;
	k[33] = 20; k[34] = 22; k[35] = 23;

	HR(mIB->Unlock());
}

void Cube::Draw()
{
	HR(gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPosCol)));
	HR(gD3DDevice->SetVertexDeclaration(VertexPosCol::decl));
	HR(gD3DDevice->SetIndices(mIB));

	HR(gD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12));
}
