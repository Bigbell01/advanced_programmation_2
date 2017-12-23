#include "Text.h"

Text::Text()
	: mFont(nullptr)
{
	SetColor(255, 255, 255, 255);

	desc.Height = 80;
	desc.Width = 40;
	desc.MipLevels = 0;
	desc.Italic = true;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(desc.FaceName, L"Times New Roman");
	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(L"");
}

Text::Text(std::wstring text, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	SetColor(r, g, b, a);

	desc.Height = 80;
	desc.Width = 40;
	desc.MipLevels = 0;
	desc.Italic = true;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(desc.FaceName, L"Times New Roman");
	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

Text::Text(std::wstring text, LPWSTR fontType, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	SetColor(r, g, b, a);

	desc.Height = 80;
	desc.Width = 40;
	desc.MipLevels = 0;
	desc.Italic = true;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(desc.FaceName, fontType);
	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

Text::Text(std::wstring text, D3DXFONT_DESC desc, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	this->desc = desc;
	this->text = text;
	SetColor(r, g, b, a);

	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

Text::Text(std::wstring text, DWORD DT_posx, DWORD DT_posy, LPWSTR fontType, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	SetColor(r, g, b, a);

	desc.Height = 80;
	desc.Width = 40;
	desc.MipLevels = 0;
	desc.Italic = true;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(desc.FaceName, fontType);
	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

Text::Text(std::wstring text, DWORD DT_posx, DWORD DT_posy, int width, int height, LPWSTR fontType, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	SetColor(r,g,b,a);

	desc.Height = height;
	desc.Width = width;
	desc.MipLevels = 0;
	desc.Italic = true;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(desc.FaceName, fontType);
	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

Text::Text(std::wstring text, D3DXFONT_DESC desc, DWORD DT_posx, DWORD DT_posy, float r, float g, float b, float a = 255)
	: mFont(nullptr)
{
	this->desc = desc;
	SetColor(r, g, b, a);

	HR(D3DXCreateFontIndirect(gD3DDevice, &desc, &mFont));

	SetText(text);
}

void Text::SetText(const std::wstring text)
{
	this->text = text;

	RECT rcRect = { 0,0,0,0 };
	if (mFont)
	{
		// calculate required rect
		mFont->DrawText(NULL, text.c_str(), text.size(), 
			&rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	GetTransform()->SetSize(
		rcRect.right - rcRect.left, 
		rcRect.bottom - rcRect.top);
}

Text::~Text()
{
	ReleaseCOM(mFont);
}

void Text::Draw2D(ID3DXSprite* spriteBatch)
{
	if (isVisible)
	{
		int r = (int)color.r;
		int g = (int)color.g;
		int b = (int)color.b;

		if (mFont)
		{
			RECT fontRect;
			fontRect.top = GetTransform()->GetPosition().y;
			fontRect.left = GetTransform()->GetPosition().x;
			fontRect.right = GetTransform()->GetSize().x;
			fontRect.bottom = GetTransform()->GetSize().y;

			HR(mFont->DrawText(0, text.c_str(), -1,
				&fontRect, 0, D3DCOLOR_XRGB(r, g, b)));
		}
	}
}