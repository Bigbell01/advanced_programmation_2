#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	BoxCollider(float centerX, float centerY, float width, float height);
	bool IsColliding(Collider * other);
	bool IsCollidingWithBox(Collider * other);
	bool IsCollidingWithCircle(Collider * other);
	bool IsCollidingWithPolygon(Collider * other);
	~BoxCollider();
private:
	
};

