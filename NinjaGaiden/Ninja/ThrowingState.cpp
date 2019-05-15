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
	spriteData.isFlipped = ninja->IsFlipped();
	 
	ninja->GetAnimationsList()[NINJA_ANI_THROWING]->Render(spriteData);

	if (ninja->GetAnimationsList()[NINJA_ANI_THROWING]->IsDone())
	{ 
		ninja->CreateThrownWeapon();
		ninja->GetAnimationsList()[NINJA_ANI_THROWING]->Reset();
		ninja->SetState(ninja->GetIdleState());
		 
	}

}
