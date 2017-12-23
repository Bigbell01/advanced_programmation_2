#include "Component.h"

std::vector<Component*> Component::components;

Component::Component()
	: isVisible(true)
{
	transform = new Transform();
	components.push_back(this);
}

Component::~Component()
{
	delete transform;
}

void Component::Update()
{
	
}

void Component::Draw2D(ID3DXSprite * spriteBatch)
{

}

void Component::Draw3D(D3DXMATRIX& view, D3DXMATRIX& proj)
{

}
