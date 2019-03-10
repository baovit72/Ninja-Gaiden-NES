#include "ThrowingState.h"

ThrowingState::ThrowingState(Simon * simon)
{
	this->simon = simon;
	simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Reset();
	simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Reset();
}
void ThrowingState::Idle()
{

}
void ThrowingState::Attack()
{

}
void ThrowingState::Walk()
{

}
void ThrowingState::Throw()
{

}
void ThrowingState::Jump()
{

}
void ThrowingState::Crouch()
{

}
void ThrowingState::Update(DWORD dt)
{
	State::Update(dt);

}
void ThrowingState::Render()
{
	State::Render();

	SpriteData spriteData;
	spriteData.width = SIMON_SPRITE_WIDTH;
	spriteData.height = SIMON_SPRITE_HEIGHT;
	spriteData.x = simon->GetPositionX();
	spriteData.y = simon->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = simon->IsLeft();

	if (simon->IsCrouching())
	{
		simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Render(spriteData);

		if (simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->IsDone())
		{
			simon->CreateThrownWeapon();
			simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Reset();
			simon->SetIsCrouching(true);
			simon->SetState(simon->GetCrouchingState());
		}
	}
	else
	{
		simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Render(spriteData);

		if (simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->IsDone())
		{
			simon->CreateThrownWeapon();
			simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Reset();
			simon->GetWhip()->ResetAnim();
			simon->SetState(simon->GetIdleState());
		}
	}
}
