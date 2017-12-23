#pragma once
#include "Collider.h"

class PolygonCollider : public Collider
{
public:
	PolygonCollider();
	PolygonCollider(std::vector<D3DXVECTOR3> points);
	bool IsColliding(Collider * other);
	bool IsCollidingWithBox(Collider * other);
	bool IsCollidingWithCircle(Collider * other);
	bool IsCollidingWithPolygon(Collider * other);
	~PolygonCollider();
private:
	
	// TODO
};

