#include "CircleCollider.h"

CircleCollider::CircleCollider()
	: Collider(0, 0, 0, 0, 0, std::vector<D3DXVECTOR3>())
{
}

CircleCollider::CircleCollider(float radius, float centerX, float centerY)
	: Collider(centerX, centerY, 0 , 0, radius, std::vector<D3DXVECTOR3>())
{
}

bool CircleCollider::IsColliding(Collider * other)
{
	// Colliding with a box
	if (other->GetRadius() == 0 && other->GetPoints().empty())
	{
		return IsCollidingWithBox(other);
	}

	// Colliding with a cricle
	if (other->GetWidth() == 0 && other->GetHeight() == 0 && other->GetPoints().empty())
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

bool CircleCollider::IsCollidingWithBox(Collider * other)
{
	float dstX = fabsf(centerX - other->GetCenterX());
	float dstY = fabsf(centerY - other->GetCenterY());

	if (dstX > (other->GetWidth() / 2 + radius / 2))
	{
		return false;
	}
	if (dstY > (other->GetHeight() / 2 + radius / 2))
	{
		return false;
	}

	if (dstX <= other->GetWidth() / 2)
	{
		return true;
	}

	if (dstY <= other->GetHeight() / 2)
	{
		return true;
	}

	float dst_sq = pow((dstX - other->GetWidth() / 2), 2) +
		pow((dstY - other->GetHeight() / 2), 2);

	return (dst_sq <= pow(radius, 2));
}

bool CircleCollider::IsCollidingWithCircle(Collider * other)
{
	float otherRadius = other->GetRadius();
	D3DXVECTOR3 otherCenter = D3DXVECTOR3((float)other->GetCenterX(), (float)other->GetCenterY(), 0);
	D3DXVECTOR3 center = D3DXVECTOR3(centerX, centerY, 0);

	float dist = D3DXVec3LengthSq(&(otherCenter - center));

	if (dist < (radius * radius) || dist < (other->GetRadius() * other->GetRadius()))
	{
		return true;
	}

	return false;
}

bool CircleCollider::IsCollidingWithPolygon(Collider * other)
{
	float radiusSq = radius * radius;
	int nbPoints = (int)other->GetPoints().size();
	D3DXVECTOR3 lastPoint = D3DXVECTOR3(other->GetPoints()[nbPoints - 1].x, 
		other->GetPoints()[nbPoints - 1].y, 0);
	D3DXVECTOR3 circleCenter = D3DXVECTOR3(centerX, centerY, 0);
	float nearestDistance = 1000000.f;
	int nearestVertex = -1;

	for (int i = 0; i < nbPoints; i++)
	{
		D3DXVECTOR3 axis = circleCenter - other->GetPoints()[i];

		float dist = D3DXVec3LengthSq(&axis) - radiusSq;

		if (dist <= 0)
		{
			return true;
		}
		else if (dist < nearestDistance)
		{
			nearestVertex = i;
			nearestDistance = dist;
		}
	}

	int index = nearestVertex - 1;
	if (index  < 0)
	{
		lastPoint = other->GetPoints()[index + nbPoints];
	}
	else
	{
		lastPoint = other->GetPoints()[index];
	}
	

	for (int i = 0; i < 2; i++)
	{
		int nextVertexIndex = nearestVertex + i;

		if (nextVertexIndex > nbPoints - 1)
		{
			nextVertexIndex -= nbPoints;
		}
		if (nextVertexIndex < 0)
		{
			nextVertexIndex += nbPoints;
		}

		D3DXVECTOR3 nextVertex = other->GetPoints()[nextVertexIndex];
		D3DXVECTOR3 edge = nextVertex - lastPoint;

		float edgeSq = D3DXVec3LengthSq(&edge);

		if (edgeSq != 0)
		{
			D3DXVECTOR3 axis = circleCenter - lastPoint;

			float dot = D3DXVec3Dot(&edge, &axis);

			if (dot >= 0 && dot <= edgeSq)
			{
				D3DXVECTOR3 projection = lastPoint + (dot / edgeSq) * edge;

				axis = projection - circleCenter;

				if (D3DXVec3LengthSq(&axis) <= radiusSq)
				{
					return true;
				}
				else
				{
					if (edge.x > 0)
					{
						if (axis.y > 0)
						{
							return false;
						}
					}
					else if (edge.x < 0)
					{
						if (axis.y < 0)
						{
							return false;
						}
					}
					else if (edge.y > 0)
					{
						if (axis.x < 0)
						{
							return false;
						}
					}
					else
					{
						if (axis.x > 0)
						{
							return false;
						}
					}
				}
			}
			else
			{
				return false;
			}
		}

		lastPoint = nextVertex;
	}

	return true;
}


CircleCollider::~CircleCollider()
{
}
