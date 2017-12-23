#pragma once
#include <vector>
#include "Component.h"

class Collider : public Component
{
public:
	Collider();
	Collider(float centerX, float centerY, float width,
		float height, float radius, std::vector<D3DXVECTOR3> points);
	virtual bool IsColliding(Collider * other);
	virtual bool IsCollidingWithBox(Collider * other);
	virtual bool IsCollidingWithCircle(Collider * other);
	virtual bool IsCollidingWithPolygon(Collider * other);
	void Update();
	virtual ~Collider();

	float GetRadius() const
	{
		return radius;
	}

	int GetCenterX() const
	{
		return (int)centerX;
	}

	int GetCenterY() const
	{
		return (int)centerY;
	}

	int GetWidth() const
	{
		return (int)width;
	}

	int GetHeight() const
	{
		return (int)height;
	}

	std::vector<D3DXVECTOR3> GetPoints() const
	{
		return points;
	}

	void SetMoveVector(D3DXVECTOR3 * move)
	{
		moveVector = move;
	}

	void SetRotationCenter(D3DXVECTOR3 * rot)
	{
		rotationCenter = rot;
	}

	D3DXVECTOR3 * GetRotationCenter() const
	{
		return rotationCenter;
	}

	void SetMoveSpeed(const float speed)
	{
		this->speed = speed;
	}

	void SetRotation(D3DXMATRIX rot)
	{
		rotation = rot;
	}

	void SetPoint(int index, D3DXVECTOR3 point)
	{
		if (index < points.size() && index > -1)
		{
			points[index] = point;
		}
	}

	void SetPosition(float x, float y)
	{
		centerX = x;
		centerY = y;
	}
protected:
	float centerX; // for all colliders
	float centerY; // for all colliders
	float width;  // for box colliders
	float height; // for box colliders
	float radius; // for circle colliders
	std::vector<D3DXVECTOR3> points; // for polygon colliders
	D3DXVECTOR3 * moveVector;
	D3DXVECTOR3 * rotationCenter;
	D3DXMATRIX rotation;
	float speed;
};

