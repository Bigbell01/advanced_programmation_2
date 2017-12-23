#pragma once

#include "Engine.h"
#include "Collider.h"

class Sprite :
	public Component
{
public:
	Sprite();
	Sprite(std::wstring path);
	Sprite(std::wstring path, Transform& transform);
	
	virtual ~Sprite();

	void SetTexture(std::wstring path)
	{
		textureInfo = gResources->GetTexture(path);

		transform->srcW = textureInfo->info.Width;
		transform->srcH = textureInfo->info.Height;
		transform->centerX = textureInfo->info.Width / 2;
		transform->centerY = textureInfo->info.Height / 2;
	}

	bool GetIsCollidingWithOtherCircle(Sprite* sprite2);
	bool GetIsCollidingWithBox(Sprite* sprite2);

	D3DXVECTOR3 GetNormalWithOtherCircle(Sprite * otherCircle);
	D3DXVECTOR3 GetVectorDirectorBetweenMouseAndSprite();

	void RotateTowardsMouse();

	virtual void Update();
	void Draw2D(ID3DXSprite* spriteBatch);

private:
	static int order;
	
	ResourceInfo* textureInfo;

};

