#pragma once

#include <vector>
#include "Transform.h"

class Component
{

friend class Engine;

public:
	Component();
	virtual ~Component();

	virtual void Update();

	/// Deprecated
	virtual void Draw(ID3DXSprite* spriteBatch) { Draw2D(spriteBatch); }

	virtual void Draw2D(ID3DXSprite* spriteBatch);
	virtual void Draw3D(D3DXMATRIX& view, D3DXMATRIX& proj);

	void SetVisible(bool tf) { isVisible = tf; }
	bool GetIsVisible() const { return isVisible; }
	Transform* GetTransform() { return transform; }

protected:
	bool isVisible;
	Transform* transform;

private:
	static std::vector<Component*> components;

};

