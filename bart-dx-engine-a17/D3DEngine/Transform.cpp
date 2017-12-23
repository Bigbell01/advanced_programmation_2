#include "Transform.h"

Transform::Transform()
	: srcX(0), srcY(0)
	, srcW(0), srcH(0)
	, centerX(0), centerY(0)
	, scaleX(1), scaleY(1)
	, posTemp(0.f, 0.f, 0.f)
	, centerTemp(0.f, 0.f, 0.f)
	, angle(0)
{
	D3DXMatrixIdentity(&T);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&world);
}

Transform::~Transform()
{
}

void Transform::SetPosition(float x, float y, float z)
{
	// TODO -- Y-UP
	D3DXMatrixTranslation(&T, x, y, z);	
	InvalidateTransform();
}

void Transform::SetPosition(const D3DXVECTOR3& position)
{
	SetPosition(position.x, position.y, position.z);
	InvalidateTransform();
}
void Transform::SetScale(const D3DXVECTOR3& scale)
{
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	InvalidateTransform();
}
void Transform::SetRotation(const D3DXMATRIX& rotation)
{	
	this->rotation = rotation;
	InvalidateTransform();
}

void Transform::SetRotation(const D3DXVECTOR3 & euler)
{
	SetRotation(euler.x, euler.y, euler.z);
	InvalidateTransform();
}

void Transform::SetRotation(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(&rotation, x, y, z);
	InvalidateTransform();
}

/// Override all transformation matrices
void Transform::SetTransform(const D3DXMATRIX& m)
{
	world = m;
}

void Transform::SetTransform(const D3DXVECTOR3& position, const D3DXMATRIX& rotation, const D3DXVECTOR3& scale)
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
}
void Transform::SetTransform(const D3DXVECTOR3& position, const D3DXVECTOR3& rotation, const D3DXVECTOR3& scale)
{
	SetTransform(position, rotation, scale);
}

void Transform::InvalidateTransform()
{
	SetTransform(S * rotation * T); 
}

//void Transform::Move(const D3DXVECTOR3& direction)
//{
//	SetPosition(GetPosition() + direction);
//}
//
//void Transform::Move(const D3DXVECTOR3& direction, const float speed)
//{
//	SetPosition(GetPosition() + direction * speed);
//}
//
//void Transform::Rotate2D(float angle)
//{
//	this->angle = angle;
//	float tempX = 0;
//	float tempY = 0;
//	GetPosition(tempX, tempY);
//	D3DXMATRIX matTranslate;
//	D3DXMATRIX matTranslate2;
//	D3DXMATRIX matRot;
//	D3DXMatrixTranslation(&matTranslate, -tempX, -tempY, 0);
//	D3DXMatrixRotationZ(&matRot, this->angle);
//	D3DXMatrixTranslation(&matTranslate2, tempX, tempY, 0);
//
//	rotation = matTranslate * matRot * matTranslate2;
//}