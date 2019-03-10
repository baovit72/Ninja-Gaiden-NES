#include "State.h"
#include "Simon.h"

void State::Update(DWORD dt)
{
	simon->SetPositionX(simon->GetPositionX() + simon->GetSpeedX()* dt);
	simon->SetPositionY(simon->GetPositionY() + simon->GetSpeedY()* dt);

	simon->SetSpeedY(simon->GetSpeedY() + SIMON_GRAVITY);
	if (simon->GetPositionY() > 100)
	{
		simon->SetSpeedY(simon->GetSpeedY() + SIMON_GRAVITY);
		simon->SetPositionY(100);
		simon->SetSpeedX(0);
		simon->SetIsGrounded(true);
	}
	if (simon->GetSpeedX() > 0 && simon->GetPositionX() > SCREEN_WIDTH - SIMON_SPRITE_WIDTH)
		simon->SetPositionX(SCREEN_WIDTH - SIMON_SPRITE_WIDTH);
	if (simon->GetSpeedX() < 0 && simon->GetPositionX() < 0)
		simon->SetPositionX(0);
	vector<Subweapon *> subweapons = simon->GetSubweapon();
	if (subweapons.size() > 0)
	{
		for (int i = 0; i < subweapons.size(); i++)
		{
			if (subweapons[i]->GetSpeedX() > 0 && subweapons[i]->GetPositionX() > SCREEN_WIDTH - SIMON_SPRITE_WIDTH)
				subweapons.erase(subweapons.begin() + i);
			else if (subweapons[i]->GetSpeedX() < 0 && subweapons[i]->GetPositionX() < 0)
				subweapons.erase(subweapons.begin() + i);
		}
	}
}

void State::Render()
{
	vector <Subweapon *> subweapons = simon->GetSubweapon();
	if (subweapons.size() > 0)
	{
		for (int i = 0; i < subweapons.size(); i++)
		{
			SpriteData spriteData;
			subweapons[i]->Render(spriteData);
		}
	}
}