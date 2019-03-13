#include "State.h"
#include "Ninja.h"
#include "Game.h"

void State::Update(DWORD dt)
{
	ninja->SetPositionX((int)(ninja->GetPositionX() + ninja->GetSpeedX()* dt));
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
		ninja->SetPositionX(0);

	vector<Subweapon *> subweapons = ninja->GetSubweapon();
	if (subweapons.size() > 0)
	{
		for (int i = 0; i < subweapons.size(); i++)
		{
			if (subweapons[i]->GetSpeedX() > 0 && subweapons[i]->GetPositionX() > SCREEN_WIDTH - NINJA_SPRITE_WIDTH)
				subweapons.erase(subweapons.begin() + i);
			else if (subweapons[i]->GetSpeedX() < 0 && subweapons[i]->GetPositionX() < 0)
				subweapons.erase(subweapons.begin() + i);
		}
	}
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