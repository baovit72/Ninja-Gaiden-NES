#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"

struct SpriteData {
	int width;
	int height;
	float x;
	float y;
	float scale = 1;
	float angle = 0;
	bool isLeft = false;
	bool isFlipped = false;
};
class Sprite
{
	int width;
	int height;
	float x;
	float y;
	float scale;
	float angle;
	bool flipHorizontal;
	bool flipVertical;

	RECT rect;
	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(LPCWSTR filePath, RECT rect, D3DCOLOR transColor);

	void SetTexture(LPCWSTR filePath, D3DCOLOR transColor);
	void SetRect(RECT rect);
	void SetData(SpriteData spriteData);

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; };
	RECT GetRect() { return rect; };
	float GetAngle() { return angle; };
	D3DXVECTOR2 GetCenter();
	D3DXVECTOR2 GetTranslate();
	D3DXVECTOR2 GetScaling();
};

