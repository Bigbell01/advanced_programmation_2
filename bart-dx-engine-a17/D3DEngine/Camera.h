#pragma once

#include "Component.h"
#include "D3DApp.h"

class Camera :
	public Component
{
public:
	Camera(float width, float height);

	void Update();

	void SetTarget(D3DXVECTOR3& targetPos)
	{
		target = targetPos;		
	}

	void SetUp(D3DXVECTOR3& up)
	{
		up *= -1;
		this->up = up;
	}

	D3DXMATRIX GetView() { return view; }
	D3DXMATRIX GetProj() { return proj; }
	D3DXVECTOR3 GetTarget() { return target; }

	virtual ~Camera();

private:
	float width, height;
	D3DXVECTOR3 up;
	D3DXVECTOR3 target;
	D3DXMATRIX view;
	D3DXMATRIX proj;
};

