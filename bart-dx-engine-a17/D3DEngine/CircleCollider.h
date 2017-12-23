#pragma once
#include "Collider.h"
#include <math.h>
#include "d3dx9.h"

class CircleCollider : public Collider
{
public:
	CircleCollider();
	CircleCollider(float radius, float centerX, float centerY);
	bool IsColliding(Collider * other);
	bool IsCollidingWithBox(Collider * other);
	bool IsCollidingWithCircle(Collider * other);
	bool IsCollidingWithPolygon(Collider * other);
	float GetRadius() const
	{
		return radius;
	}

	~CircleCollider();
private: 
	
};

