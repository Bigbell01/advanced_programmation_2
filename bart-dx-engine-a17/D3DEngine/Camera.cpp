#include "Camera.h"

Camera::Camera(float width, float height)
	: up(0.f, -1.f, 0.f)
	, target(0.f, 0.f, 0.f)
	, width(width)
	, height(height)
{
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(&view, &GetTransform()->GetPosition(), &target, &up);
	D3DXMatrixOrthoLH(&proj, width, height, 0.01f, 1000.0f);
	//D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI/4, width/height, 0.01f, 1000.0f);

	HR(gD3DDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &proj));
}

Camera::~Camera()
{
}
