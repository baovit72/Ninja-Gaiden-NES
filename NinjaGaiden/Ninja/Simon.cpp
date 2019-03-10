#include "Simon.h"

vector<Animation *> Simon::animations = vector<Animation *>();
vector<Subweapon *> Simon::subweapons = vector<Subweapon *>();
Simon * Simon::__instance = NULL;

Simon::Simon()
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
Simon * Simon::GetInstance()
{
	if (__instance == NULL)
		__instance = new Simon();
	return __instance;
}
void Simon::LoadResources()
{
	// 0
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 1
	anim = new Animation(100);
	for (int i = 0; i < 4; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 2
	anim = new Animation(150);
	for (int i = 5; i < 8; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 3
	anim = new Animation(150);
	for (int i = 15; i < 18; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 4
	anim = new Animation(100);
	for (int i = 4; i < 5; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 5
	anim = new Animation(100);
	for (int i = 4; i < 5; i++)
	{
		RECT rect;
		rect.left = (i % SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_WIDTH;
		rect.right = rect.left + SIMON_SPRITE_WIDTH;
		rect.top = (i / SIMON_TEXTURE_COLUMNS) * SIMON_SPRITE_HEIGHT;
		rect.bottom = rect.top + SIMON_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SIMON_TEXTURE_LOCATION, rect, SIMON_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
void Simon::SetState(State * state)
{
	this->state = state;
}
State * Simon::GetIdleState()
{
	return idleState;
}
State * Simon::GetWalkingState()
{
	return walkingState;
}
State * Simon::GetAttackingState()
{
	return attackingState;
}
State * Simon::GetThrowingState()
{
	return throwingState;
}
State * Simon::GetCrouchingState()
{
	return crouchingState;
}
State * Simon::GetJumpingState()
{
	return jumpingState;
}

//Các hàm hành động nhân vật
void Simon::Idle()
{
	state->Idle();
}
void Simon::Attack()
{
	state->Attack();
}
void Simon::Walk()
{
	state->Walk();
}
void Simon::Throw()
{
	state->Throw();
}
void Simon::Jump()
{
	state->Jump();
}
void Simon::Crouch()
{
	state->Crouch();
}
void Simon::TurnLeft()
{
	whip->TurnLeft();
	isLeft = true;
}
void Simon::TurnRight()
{
	whip->TurnRight();
	isLeft = false;
}
void Simon::CreateThrownWeapon()
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
void Simon::Update(DWORD dt)
{
	whip->Update(dt);
	for (int i = 0; i < subweapons.size(); i++)
	{
		subweapons[i]->Update(dt);
	}
	state->Update(dt);
}
//Hàm render
void Simon::Render()
{
	state->Render();
}