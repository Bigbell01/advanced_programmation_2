#pragma once

#include "Timer.h"
#include "D3DUtils.h"

class Transform
{
	friend class Sprite;
	friend class Text;

public:
	Transform();
	~Transform();

	void SetPosition(float x, float y, float z);
	void SetPosition(const D3DXVECTOR3& position);
	void SetScale(const D3DXVECTOR3& scale);
	void SetRotation(const D3DXMATRIX& rotation);
	void SetRotation(const D3DXVECTOR3& euler);
	void SetRotation(float x, float y, float z);
	D3DXMATRIX GetRotation() { return rotation; }
	void SetTransform(const D3DXMATRIX& m);
	void SetTransform(const D3DXVECTOR3& position, const D3DXMATRIX& rotation, const D3DXVECTOR3& scale);
	void SetTransform(const D3DXVECTOR3& position, const D3DXVECTOR3& rotation, const D3DXVECTOR3& scale);
	
	D3DXMATRIX GetWorld() 
	{ 
		return world; 
	}

	D3DXVECTOR3 GetPosition()
	{
		return D3DXVECTOR3(T._41, T._42, T._43) ;
	}

	void SetSize(int width, int height) 
	{ 
		srcW = width; 
		srcH = height; 
	}

	D3DXVECTOR3 GetSize()
	{
		D3DXVECTOR3 size((float)srcW, (float)srcH, 0);
		return size;
	}

	//D3DXVECTOR3 GetPosition(D3DXVECTOR3& position)
	//{
	//	position.x = this->dstX;
	//	position.y = this->dstY;
	//	if (!position.z)
	//		position.z = 0;
	//	return position;
	//}
	//D3DXVECTOR3 GetPosition(float& x, float& y)
	//{
	//	x = dstX;
	//	y = dstY;
	//	D3DXVECTOR3 tempPos(x, y, 0);
	//	return tempPos;
	//} 

	void SetCenter(const D3DXVECTOR3& center)
	{
		centerX = (int)center.x;
		centerY = (int)center.y;
	}
	
	float GetAngle() { return angle; };
	
	//void Rotate2D(float angle);
	//void Move(const D3DXVECTOR3& direction);
	//void Move(const D3DXVECTOR3& direction, const float speed);

private:

	void InvalidateTransform();

	int srcX, srcY;
	int srcW, srcH;
	int centerX, centerY;
	float scaleX, scaleY;

	float angle;

	D3DXMATRIX T;
	D3DXMATRIX rotation;
	D3DXMATRIX S;
	int localOrder;

	// Pool for Position Getters/Setters
	D3DXVECTOR3 scaleTemp;
	D3DXVECTOR3 posTemp;
	D3DXVECTOR3 centerTemp;
	RECT srcTemp;

	D3DXMATRIX world;
};