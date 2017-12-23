#include "PolygonCollider.h"



PolygonCollider::PolygonCollider()
	: Collider(0, 0, 0, 0, 0, std::vector<D3DXVECTOR3>())
{
}

PolygonCollider::PolygonCollider(std::vector<D3DXVECTOR3> points)
	: Collider(0, 0, 0, 0, 0, points)
{
}

bool PolygonCollider::IsColliding(Collider * other)
{
	// Colliding with a box
	if (other->GetRadius() == 0 && GetPoints().empty())
	{
		return other->IsCollidingWithBox(this);
	}

	// Colliding with a cricle
	if (other->GetWidth() == 0 && other->GetHeight() == 0 && GetPoints().empty())
	{
		return other->IsCollidingWithPolygon(this);
	}

	// Colliding with a polygon
	if (other->GetRadius() == 0 && other->GetWidth() == 0 && other->GetHeight() == 0)
	{
		return IsCollidingWithPolygon(other);
	}

	return false;
}

bool PolygonCollider::IsCollidingWithBox(Collider * other)
{
	return false;
}

bool PolygonCollider::IsCollidingWithCircle(Collider * other)
{
	return false;
}

bool PolygonCollider::IsCollidingWithPolygon(Collider * other)
{
	return false;
}


PolygonCollider::~PolygonCollider()
{
}
