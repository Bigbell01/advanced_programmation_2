#include "Sprite.h"

Sprite::Sprite()
	: textureInfo(nullptr)

{
}

Sprite::Sprite(std::wstring path)
	: textureInfo(nullptr)
{
	SetTexture(path);
}

Sprite::Sprite(std::wstring path, Transform& transform)
	: textureInfo(nullptr)
{
	this->transform = &transform;

	SetTexture(path);
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
}

bool Sprite::GetIsCollidingWithOtherCircle(Sprite * sprite2)
{
	float dx = (this->transform->GetPosition().x) - (sprite2->transform->GetPosition().x);
	float dy = (this->transform->GetPosition().y) - (sprite2->transform->GetPosition().y);
	float distance = sqrt(dx * dx + dy * dy);
	float sprt1Rad = this->transform->srcW / 2;
	float sprt2Rad = sprite2->transform->srcW / 2;

	if (distance < sprt1Rad + sprt2Rad || distance == 0)
		return true;

	return false;
}

bool Sprite::GetIsCollidingWithBox(Sprite* sprite2)
{
	//calculate distance in Y of the two objects
	float dx = (this->transform->GetPosition().x) - (sprite2->transform->GetPosition().x);
	float dy = (this->transform->GetPosition().y) - (sprite2->transform->GetPosition().y);

	//return the absolute value of dy and dx
	if (dy < 0)
		dy *= -1;
	if (dx < 0)
		dx *= -1;

	if (dy < (this->transform->srcH / 2) + (sprite2->transform->srcH / 2))
		if (dx < (this->transform->srcW / 2) + (sprite2->transform->srcW / 2))
			return true;

	return false;
}

D3DXVECTOR3 Sprite::GetNormalWithOtherCircle(Sprite * sprite2)
{
	float dx = (this->transform->GetPosition().x) - (sprite2->transform->GetPosition().x);
	float dy = (this->transform->GetPosition().y) - (sprite2->transform->GetPosition().y);
	float distance = sqrt(dx * dx + dy * dy);
	D3DXVECTOR3 dst = D3DXVECTOR3(dx / distance, dy / distance, 0);
	return dst;
}

D3DXVECTOR3 Sprite::GetVectorDirectorBetweenMouseAndSprite()
{
	WINDOWINFO windowInfo;
	GetWindowInfo(gEngine->GetMainWindow(), &windowInfo);
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	float tempX = 0;
	float tempY = 0;
	//transform.GetPosition(tempX, tempY);

	float normalX = (windowInfo.rcWindow.right - windowInfo.rcWindow.left) / 2 + windowInfo.rcWindow.left + tempX - cursorPos.x;
	float normalY = (windowInfo.rcWindow.bottom - windowInfo.rcWindow.top) / 2 + windowInfo.rcWindow.top + tempY - cursorPos.y;
	float distance = sqrt(normalX * normalX + normalY * normalY);
	D3DXVECTOR3 normal = D3DXVECTOR3((normalX / distance) * -1, (normalY / distance) * -1,0);
	return normal;
}

void Sprite::RotateTowardsMouse()
{
	WINDOWINFO windowInfo;
	GetWindowInfo(gEngine->GetMainWindow(), &windowInfo);
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	float tempX = 0;
	float tempY = 0; 

	// TODO - BUG
	//transform.GetPosition(tempX, tempY);
	float l = (windowInfo.rcWindow.right - windowInfo.rcWindow.left) / 2 + windowInfo.rcWindow.left + tempX - cursorPos.x;
	float h = (windowInfo.rcWindow.bottom - windowInfo.rcWindow.top) / 2 + windowInfo.rcWindow.top + tempY - cursorPos.y;
	float angle = atan2(h, l);
	//transform.Rotate2D(angle + D3DX_PI / 2);
}

void Sprite::Draw2D(ID3DXSprite* spriteBatch)
{
	if (textureInfo)
	{
		if (isVisible)
		{
			transform->srcTemp.left = transform->srcX;
			transform->srcTemp.top = transform->srcY;
			transform->srcTemp.right = transform->srcW;
			transform->srcTemp.bottom = transform->srcH;
					 
			transform->centerTemp.x = transform->centerX;
			transform->centerTemp.y = transform->centerY;
			//transform.centerTemp.z = localOrder;
					 
			transform->posTemp.x = transform->GetPosition().x;
			transform->posTemp.y = transform->GetPosition().y;
			//transform.posTemp.z = localOrder;

			spriteBatch->SetTransform(&this->GetTransform()->GetWorld());
			//spriteBatch->SetTransform(&(transform.GetRotation()));
			
			HR(spriteBatch->Draw(textureInfo->texture, 
				&transform->srcTemp, &transform->centerTemp, 
				0, D3DCOLOR_XRGB(255, 255, 255)));
			
			//D3DXMATRIX I;
			//D3DXMatrixIdentity(&I);
			//spriteBatch->SetTransform(&I);


			spriteBatch->Flush();
		}
	}
}
