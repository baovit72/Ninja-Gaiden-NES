#include "Viewport.h"
#include "Ninja.h"
#include "Game.h"
#include "Debug.h"

Viewport * Viewport::__instance = NULL;

Viewport::Viewport()
{
	width = 313;
	height = 176;
	x = 0;
	y = 176;
}


Viewport::~Viewport()
{

}


Viewport * Viewport::GetInstance()
{
	if (__instance == NULL)
		__instance = new Viewport();
	return __instance;
}
void Viewport::Update(DWORD dt)
{
	Ninja * ninja = Ninja::GetInstance();
	int rightBoundary = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() - SCREEN_WIDTH / 2);
	int leftBoundary = (int)SCREEN_WIDTH / 2;
	if (ninja->GetPositionX() > leftBoundary && ninja->GetPositionX() < rightBoundary)
	{
		this->x = ninja->GetPositionX() - leftBoundary;
	}

}
void Viewport::SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1;
	mt._41 = -this->x;
	mt._42 = this->y;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;
	D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);
	D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}

