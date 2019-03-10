#include "CrouchingState.h"


CrouchingState::CrouchingState(Simon * simon)
{
	this->simon = simon;
}
void CrouchingState::Idle()
{
	simon->SetIsCrouching(false);
	simon->SetState(simon->GetIdleState());
}
void CrouchingState::Attack()
{
	simon->SetState(simon->GetAttackingState());
}
void CrouchingState::Walk()
{

}
void CrouchingState::Throw()
{
	simon->SetState(simon->GetThrowingState());
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
	spriteData.width = SIMON_SPRITE_WIDTH;
	spriteData.height = SIMON_SPRITE_HEIGHT;
	spriteData.x = simon->GetPositionX();
	spriteData.y = simon->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = simon->IsLeft();

	simon->GetAnimationsList()[SIMON_ANI_CROUCHING]->Render(spriteData);
}