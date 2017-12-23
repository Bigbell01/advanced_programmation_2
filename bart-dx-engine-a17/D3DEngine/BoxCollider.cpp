#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: Collider(0, 0, 0, 0, 0, std::vector<D3DXVECTOR3>())
{
}

BoxCollider::BoxCollider(float centerX, float centerY, float width, float height)
	: Collider(centerX, centerY, width, height, 0, std::vector<D3DXVECTOR3>())
{
}

bool BoxCollider::IsColliding(Collider * other)
{
	// Colliding with a box
	if (other->GetRadius() == 0 && GetPoints().empty())
	{
		return IsCollidingWithBox(other);
	}

	// Colliding with a cricle
	if (other->GetWidth() == 0 && other->GetHeight() == 0 && GetPoints().empty())
	{
		return IsCollidingWithCircle(other);
	}

	// Colliding with a polygon
	if (other->GetRadius() == 0 && other->GetWidth() == 0 && other->GetHeight() == 0)
	{
		return IsCollidingWithPolygon(other);
	}

	return false;
}

bool BoxCollider::IsCollidingWithBox(Collider * other)
{
	return false;
}

bool BoxCollider::IsCollidingWithCircle(Collider * other)
{
	return other->IsCollidingWithBox(this);
}

bool BoxCollider::IsCollidingWithPolygon(Collider * other)
{
	return false;
}


BoxCollider::~BoxCollider()
{
}
