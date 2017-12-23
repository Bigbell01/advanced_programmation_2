#pragma once
#include "d3dx9.h"

struct AABB
{
	const float IINFINITY = FLT_MAX;
	const float EPSILON = 0.001f;

	AABB()
		: minPt(IINFINITY, IINFINITY, IINFINITY),
		maxPt(-IINFINITY, -IINFINITY, -IINFINITY)
	{
	}

	D3DXVECTOR3 Center()
	{
		return 0.5f * (minPt + maxPt);
	}

	D3DXVECTOR3 minPt;
	D3DXVECTOR3 maxPt;
};

struct BoundingSphere
{
	BoundingSphere()
		: pos(0.0f, 0.0f, 0.0f),
		radius(0.0f)
	{
	}

	D3DXVECTOR3 pos;
	float radius;
};