#include "AttackingState.h"

AttackingState::AttackingState(Simon * simon)
{
	this->simon = simon;
	simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Reset();
	simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Reset();
	simon->GetWhip()->ResetAnim();
}
void AttackingState::Idle()
{

}
void AttackingState::Attack()
{

}
void AttackingState::Walk()
{
	
}
void AttackingState::Throw()
{

}
void AttackingState::Jump()
{

}
void AttackingState::Crouch()
{

}
void AttackingState::Update(DWORD dt)
{
	State::Update(dt);

}
void AttackingState::Render()
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

	simon->GetWhip()->SetPosition(simon->GetPositionX(), simon->GetPositionY(), simon->IsCrouching());
	if (simon->IsCrouching())
	{
		simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Render(spriteData);
		simon->GetWhip()->Render(spriteData);

		if (simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->IsDone())
		{
			simon->GetAnimationsList()[SIMON_ANI_CROUCHING_ATTACKING]->Reset();
			simon->GetWhip()->ResetAnim();
			simon->SetIsCrouching(true);
			simon->SetState(simon->GetCrouchingState());
		}
	}
	else
	{
		simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Render(spriteData);
		simon->GetWhip()->Render(spriteData);

		if (simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->IsDone())
		{
			simon->GetAnimationsList()[SIMON_ANI_STANDING_ATTACKING]->Reset();
			simon->GetWhip()->ResetAnim();
			simon->SetState(simon->GetIdleState());
		}
	}
}
