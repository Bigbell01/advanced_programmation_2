#pragma once

#include "D3DApp.h"
#include "Vertex.h"
#include <vector>

class Trigrid
{
public:
	Trigrid();
	~Trigrid();

	void GenTriGrid(int numVertRows, int numVertCols, float dx, float dz,
		const D3DXVECTOR3& center, std::vector<D3DXVECTOR3>& verts,
		std::vector<DWORD>& indices);

};

