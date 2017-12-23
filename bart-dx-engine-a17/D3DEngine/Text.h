#pragma once

#include "Engine.h"
#include "Transform.h"

class Text
	: public Component
{
public:
	Text();
	Text(std::wstring text, float r, float g, float b, float a);
	Text(std::wstring text, LPWSTR fontType, float r, float g, float b, float a);
	Text(std::wstring text, D3DXFONT_DESC desc, float r, float g, float b, float a);
	Text(std::wstring text, DWORD DT_posx, DWORD DT_posy, LPWSTR fontType, float r, float g, float b, float a);
	Text(std::wstring text, D3DXFONT_DESC desc, DWORD DT_posx, DWORD DT_posy, float r, float g, float b, float a);
	Text(std::wstring text, DWORD DT_posx, DWORD DT_posy, int width, int height, LPWSTR fontType, float r, float g, float b, float a);
	~Text();

	void SetColor(const int r, const int g, const int b, const int a) 
	{ 
		color.r = r; 
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void SetText(const std::wstring text);
	void Draw2D(ID3DXSprite* spriteBatch);

protected:

private:
	std::wstring text;
	D3DXFONT_DESC desc;
	ID3DXFont* mFont;
	D3DXCOLOR color;
};

