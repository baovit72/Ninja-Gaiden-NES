#pragma once
#include "d3d9.h"
#include "d3dx9.h"

class Viewport
{
	static Viewport * __instance;
	Viewport();
	int width;
	int height;
	int x = 0;
	int y = 176;
public:
	static Viewport * GetInstance();
	~Viewport();

	RECT GetRect();
	void ResetPosition();
	void Update(DWORD dt);
	void SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling);
};