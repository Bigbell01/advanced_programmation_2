#pragma once

#include "stdafx.h"

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);

// Surcharges d'opérateurs
inline std::ostream& operator<<(std::ostream& os, D3DXVECTOR3& v)
{
	return os << "X: " << v.x << ", Y: " << v.y << ", Z: " << v.z;
}

inline std::ostream& operator<<(std::ostream& os, D3DXVECTOR4& v)
{
	return os << "X: " << v.x << ", Y: " << v.y << ", Z: " << v.z << ", W: " << v.w;
}

inline std::ostream& operator<<(std::ostream& os, D3DXMATRIX& m)
{
	for (int i = 0; i < 4; ++i)
	{
		os << "| ";
		for (int j = 0; j < 4; ++j)
		{
			os << m(i, j);
			if (j < 3)
				os << ", ";
		}
		os << " |" << std::endl;
	}
	return os;
}

#define ReleaseCOM(x)\
{\
	if(x)\
	{\
		x->Release();\
		x = 0;\
	}\
}

// Macro
#if defined(DEBUG) | defined(_DEBUG)

#ifndef HR

#define HR(x)\
{\
	if(x)\
	{\
		HRESULT hr = x;\
		if (FAILED(hr))\
		{\
			DXTrace(__FILE__, __LINE__, hr, L#x, true);\
		}\
	}\
}
#endif

#else

#ifndef HR
#define HR(x) x;
#endif

#endif