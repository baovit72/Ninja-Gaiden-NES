﻿#include "Ninja.h"

vector<Animation *> Ninja::animations = vector<Animation *>();
vector<Subweapon *> Ninja::subweapons = vector<Subweapon *>();
Ninja * Ninja::__instance = NULL;

Ninja::Ninja()
{
	LoadResources();

	whip = new Whip(this);

	idleState = new IdleState(this);
	walkingState = new WalkingState(this);
	crouchingState = new CrouchingState(this);
	jumpingState = new JumpingState(this);
	attackingState = new AttackingState(this);
	throwingState = new ThrowingState(this);

	state = idleState;

	this->x = 100;
	this->y = 100;
	this->width = NINJA_SPRITE_WIDTH;
	this->height = NINJA_SPRITE_HEIGHT;
	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = NINJA_SPRITE_WIDTH;
	collider.height = NINJA_SPRITE_HEIGHT;
}
Ninja * Ninja::GetInstance()
{
	if (__instance == NULL)
		__instance = new Ninja();
	return __instance;
}
void Ninja::LoadResources()
{
	// 0 - Idle
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

	// 1 - Walking
	anim = new Animation(50);
	for (int i = 1; i < 4; i++)
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

	// 2 -  Attacking Whip
	anim = new Animation(120);
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
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// 3 - Crouching Attacking
	anim = new Animation(120);
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
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// 4 - Jumping
	anim = new Animation(130);
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

	// 5 - Crouching
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
	// 6- Climbing
	anim = new Animation(120);
	for (int i = 4; i <= 5; i++) {
		RECT rect;
		rect.left = (i% NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite *sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// 7- Rolling  
	anim = new Animation(120);
	for (int i = 15; i < 19; i++) {
		RECT rect;
		rect.left = (i% NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite *sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 8 - Throwing

	anim = new Animation(50);
	for (int i = 20; i < 23; i++) {
		RECT rect;
		rect.left = (i% NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS)*NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite *sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);
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
	Subweapon * subweapon = NULL;
	switch (curSubweapon)
	{
	case SUBWEAPON_KNIFE:
		subweapon = new  Knife();
		break;
	case SUBWEAPON_FIREWHEEL:
		subweapon = new FireWheel();
		break;
	case SUBWEAPON_THROWINGSHURIKEN:
		subweapon = new ThrowingShuriken();
		break;
	case SUBWEAPON_WINDMILLSHURIKEN:
		subweapon = new WindmillShuriken();
		break;
	case SUBWEAPON_JUMPSLASH:
		subweapon = new JumpSlash();
	default:
		break;

	}
	if (subweapon == NULL)
		return;
	if (isFlipped)
		subweapon->TurnLeft();
	else
		subweapon->TurnRight();
	subweapon->SetThrownPosition(this->x, this->y, isCrouching);
	this->subweapons.push_back(subweapon);
	 
}
void Ninja::SetSubweapon(int type) {
	this->curSubweapon = type;
}
//Hàm cập nhật
void Ninja::Update(DWORD dt)
{
	state->Update(dt);
}
//Hàm render
void Ninja::Render()
{
	state->Render();
}