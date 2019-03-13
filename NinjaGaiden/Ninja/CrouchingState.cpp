#include "CrouchingState.h"


CrouchingState::CrouchingState(Ninja * ninja)
{
	this->ninja = ninja;
}
void CrouchingState::Idle()
{
	ninja->SetIsCrouching(false);
	ninja->SetState(ninja->GetIdleState());
}
void CrouchingState::Attack()
{
	ninja->SetState(ninja->GetAttackingState());
}
void CrouchingState::Walk()
{

}
void CrouchingState::Throw()
{
	ninja->SetState(ninja->GetThrowingState());
}
void CrouchingState::Jump()
{

}
void CrouchingState::Crouch()
{

}
void CrouchingState::Update(DWORD dt)
{
	State::Update(dt);
}
void CrouchingState::Render()
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

	ninja->GetAnimationsList()[NINJA_ANI_CROUCHING]->Render(spriteData);
}