#include "Ninja.h"

vector<Animation *> Ninja::animations = vector<Animation *>();
vector<Subweapon *> Ninja::subweapons = vector<Subweapon *>();
Ninja * Ninja::__instance = NULL;

Ninja::Ninja()
{
	LoadResources();

	whip = new Whip();

	idleState = new IdleState(this);
	walkingState = new WalkingState(this);
	crouchingState = new CrouchingState(this);
	jumpingState = new JumpingState(this);
	attackingState = new AttackingState(this);
	throwingState = new ThrowingState(this);

	state = idleState;

}
Ninja * Ninja::GetInstance()
{
	if (__instance == NULL)
		__instance = new Ninja();
	return __instance;
}
void Ninja::LoadResources()
{
	// 0
	Animation * anim = new Animation(50);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 1
	anim = new Animation(50);
	for (int i = 0; i < 4; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 2
	anim = new Animation(50);
	for (int i = 10; i < 15; i++)
	{
		if (i == 10)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		else if (i == 11 || i == 13)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH * 2;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// 3
	anim = new Animation(50);
	for (int i = 25; i < 30; i++)
	{
		if (i == 25)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		else if (i == 26 || i == 28)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH * 2;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// 4
	anim = new Animation(50);
	for (int i = 6; i < 10; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 5
	anim = new Animation(50);
	for (int i = 24; i < 25; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
void Ninja::SetState(State * state)
{
	this->state = state;
}
State * Ninja::GetIdleState()
{
	return idleState;
}
State * Ninja::GetWalkingState()
{
	return walkingState;
}
State * Ninja::GetAttackingState()
{
	return attackingState;
}
State * Ninja::GetThrowingState()
{
	return throwingState;
}
State * Ninja::GetCrouchingState()
{
	return crouchingState;
}
State * Ninja::GetJumpingState()
{
	return jumpingState;
}

//Các hàm hành động nhân vật
void Ninja::Idle()
{
	state->Idle();
}
void Ninja::Attack()
{
	state->Attack();
}
void Ninja::Walk()
{
	state->Walk();
}
void Ninja::Throw()
{
	state->Throw();
}
void Ninja::Jump()
{
	state->Jump();
}
void Ninja::Crouch()
{
	state->Crouch();
}
void Ninja::TurnLeft()
{
	whip->TurnLeft();
	isLeft = true;
}
void Ninja::TurnRight()
{
	whip->TurnRight();
	isLeft = false;
}
void Ninja::CreateThrownWeapon()
{
	Subweapon * subweapon;
	switch (curSubweapon)
	{
	case SUBWEAPON_KNIFE:
		subweapon = new Knife();
		if (isLeft) 
			subweapon->TurnLeft();
		else 
			subweapon->TurnRight();
		subweapon->SetThrownPosition(this->x, this->y, isCrouching);
		this->subweapons.push_back(subweapon);
		break;
	}
}
//Hàm cập nhật
void Ninja::Update(DWORD dt)
{
	whip->Update(dt);
	for (int i = 0; i < subweapons.size(); i++)
	{
		subweapons[i]->Update(dt);
	}
	state->Update(dt);
}
//Hàm render
void Ninja::Render()
{
	state->Render();
}