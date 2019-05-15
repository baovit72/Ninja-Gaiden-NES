#include "AttackingState.h"

AttackingState::AttackingState(Ninja * ninja)
{
	this->ninja = ninja;
	ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Reset();
	ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Reset();
	ninja->GetWhip()->ResetAnim();
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
	spriteData.width = NINJA_SPRITE_WIDTH;
	spriteData.height = NINJA_SPRITE_HEIGHT;
	spriteData.x = ninja->GetPositionX();
	spriteData.y = ninja->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = ninja->IsLeft();
	spriteData.isFlipped = ninja->IsFlipped();

	//Render Whip
	
	ninja->GetWhip()->Render();


	if (ninja->IsCrouching())
	{
		ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Render(spriteData);
		//ninja->GetWhip()->Render(spriteData);


		if (ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->IsDone())
		{
			ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Reset();
			ninja->GetWhip()->ResetAnim();
			ninja->SetIsCrouching(true);
			ninja->SetState(ninja->GetCrouchingState());
		}
	}
	else
	{
		ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Render(spriteData);
		//ninja->GetWhip()->Render(spriteData);

		if (ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->IsDone())
		{
			ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Reset();
			ninja->GetWhip()->ResetAnim();
			ninja->SetState(ninja->GetIdleState());
		}
	}
}
