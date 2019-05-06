#include "State.h"
#include "Ninja.h"
#include "Game.h"

void State::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects; //Placeholder
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();

	ninja->SetSpeedY(ninja->GetSpeedY() - NINJA_GRAVITY);

	coEvents.clear();
	ninja->SetDt(dt);
	ninja->CalcPotentialCollisions(tiles, coObjects, coEvents);


	if (coEvents.size() == 0)
	{
		int moveX = trunc(ninja->GetSpeedX()* dt);
		int moveY = trunc(ninja->GetSpeedY()* dt);

		ninja->SetPositionX(ninja->GetPositionX() + moveX);
		ninja->SetPositionY(ninja->GetPositionY() + moveY);

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		ninja->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		int moveX = min_tx * ninja->GetSpeedX() * dt + nx * 0.4;
		int moveY = min_ty * ninja->GetSpeedY() * dt + ny * 0.4;

		ninja->SetPositionX((int)(ninja->GetPositionX() + moveX));
		ninja->SetPositionY((int)(ninja->GetPositionY() + moveY));


		if (nx != 0) ninja->SetSpeedX(0);
		if (ny != 0) ninja->SetSpeedY(0);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				ninja->SetIsGrounded(true);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];


	if (ninja->GetPositionY() < 0)
	{
		ninja->SetPositionX(100);
		ninja->SetPositionY(100);
		Viewport::GetInstance()->ResetPosition();
	}
	/*TiledMap * tiledMap = Game::GetInstance()->GetTiledMap();
	vector<GameObject *> solidTiles = tiledMap->GetSolidTiles();
	float normalx, normaly;

	Collider col = this->ninja->GetCollider();
	col.vx = this->ninja->GetSpeedX() * dt;
	col.vy = this->ninja->GetSpeedY() * dt;
	this->ninja->SetCollider(col);

	bool flag = false;
	float collisionTime = 1.0f;
	for (int i = 0; i < solidTiles.size(); i++)
	{
		collisionTime = Game::SweptAABB(this->ninja->GetCollider(), solidTiles[i]->GetCollider(), normalx, normaly);
	}
	col = this->ninja->GetCollider();
	float x = (int)(col.x + col.vx * collisionTime);
	float y = (int)(col.y + col.vy * collisionTime);

	this->ninja->SetPositionX(x);
	this->ninja->SetPositionY(y);

	ninja->SetSpeedY(ninja->GetSpeedY() - NINJA_GRAVITY);

	DebugOut(L"X: %f\n", ninja->GetPositionX());
	DebugOut(L"Y: %f\n", ninja->GetPositionY());*/

	
	/*ninja->SetPositionX((int)(ninja->GetPositionX() + ninja->GetSpeedX()* dt));
	ninja->SetPositionY((int)(ninja->GetPositionY() + ninja->GetSpeedY()* dt));

	ninja->SetSpeedY(ninja->GetSpeedY() - NINJA_GRAVITY);
	if (ninja->GetPositionY() < NINJA_SPRITE_HEIGHT + TILES_HEIGHT_PER_TILE)
	{
		ninja->SetSpeedY(0);
		ninja->SetPositionY(NINJA_SPRITE_HEIGHT + TILES_HEIGHT_PER_TILE);
		ninja->SetSpeedX(0);
		ninja->SetIsGrounded(true);
	}
	if (ninja->GetSpeedX() > 0 && ninja->GetPositionX() > Game::GetInstance()->GetTiledMap()->GetWidth() - NINJA_SPRITE_WIDTH)
		ninja->SetPositionX(Game::GetInstance()->GetTiledMap()->GetWidth() - NINJA_SPRITE_WIDTH);
	if (ninja->GetSpeedX() < 0 && ninja->GetPositionX() < 0)
		ninja->SetPositionX(0);*/

	/*vector<Subweapon *> subweapons = ninja->GetSubweapon();
	if (subweapons.size() > 0)
	{
		for (int i = 0; i < subweapons.size(); i++)
		{
			if (subweapons[i]->GetSpeedX() > 0 && subweapons[i]->GetPositionX() > SCREEN_WIDTH - NINJA_SPRITE_WIDTH)
				subweapons.erase(subweapons.begin() + i);
			else if (subweapons[i]->GetSpeedX() < 0 && subweapons[i]->GetPositionX() < 0)
				subweapons.erase(subweapons.begin() + i);
		}
	}*/
}

void State::Render()
{
	vector <Subweapon *> subweapons = ninja->GetSubweapon();
	if (subweapons.size() > 0)
	{
		for (int i = 0; i < subweapons.size(); i++)
		{
			SpriteData spriteData;
			subweapons[i]->Render(spriteData);
		}
	}
}