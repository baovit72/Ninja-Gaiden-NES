#include "ThrowingState.h"

ThrowingState::ThrowingState(Ninja * ninja)
{
	this->ninja = ninja;
	ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Reset();
	ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Reset();
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
	spriteData.width = NINJA_SPRITE_WIDTH;
	spriteData.height = NINJA_SPRITE_HEIGHT;
	spriteData.x = ninja->GetPositionX();
	spriteData.y = ninja->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = ninja->IsLeft();

	if (ninja->IsCrouching())
	{
		ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Render(spriteData);

		if (ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->IsDone())
		{
			ninja->CreateThrownWeapon();
			ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Reset();
			ninja->SetIsCrouching(true);
			ninja->SetState(ninja->GetCrouchingState());
		}
	}
	else
	{
		ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Render(spriteData);

		if (ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->IsDone())
		{
			ninja->CreateThrownWeapon();
			ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Reset();
			ninja->GetWhip()->ResetAnim();
			ninja->SetState(ninja->GetIdleState());
		}
	}
}
