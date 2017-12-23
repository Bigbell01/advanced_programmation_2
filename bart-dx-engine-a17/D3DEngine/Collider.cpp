#include "Collider.h"

Collider::Collider()
	: Component()
	, centerX(0)
	, centerY(0)
	, width(0)
	, height(0)
	, radius(0)
	, speed(0.0f)
{
	points = std::vector<D3DXVECTOR3>();
	moveVector = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotationCenter = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&rotation);
}

Collider::Collider(float centerX, float centerY, float width, float height, float radius, std::vector<D3DXVECTOR3> points)
	: Component()
	, centerX(centerX)
	, centerY(centerY)
	, width(width)
	, height(height)
	, radius(radius)
	, speed(0.0f)
{
	this->points = points;
	moveVector = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotationCenter = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&rotation);
}

bool Collider::IsColliding(Collider * other)
{
	return false;
}

Collider::~Collider()
{
	delete rotationCenter;
	delete moveVector;
}

bool Collider::IsCollidingWithBox(Collider * other)
{
	return false;
}

bool Collider::IsCollidingWithCircle(Collider * other)
{
	return false;
}

bool Collider::IsCollidingWithPolygon(Collider * other)
{
	return false;
}

void Collider::Update()
{
	centerX += moveVector->x * speed;
	centerY += moveVector->y * speed;
}
