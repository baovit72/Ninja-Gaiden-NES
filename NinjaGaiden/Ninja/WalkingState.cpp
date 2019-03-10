#include "WalkingState.h"

WalkingState::WalkingState(Simon * simon)
{
	this->simon = simon;
}
void WalkingState::Idle()
{
	simon->SetSpeedX(0);

	simon->SetState(simon->GetIdleState());
}
void WalkingState::Attack()
{
	simon->SetSpeedX(0);
	simon->SetState(simon->GetAttackingState());
}
void WalkingState::Walk()
{
	simon->SetSpeedX(SIMON_WALKING_SPEED * (simon->IsLeft() ? -1 : 1));
}
void WalkingState::Throw()
{
	simon->SetSpeedX(0);
	simon->SetState(simon->GetThrowingState());
}
void WalkingState::Jump()
{
	if (simon->IsGrounded())
	{
		simon->SetIsGrounded(false);
		simon->SetSpeedY(-SIMON_JUMP_SPEED_Y);
		simon->SetState(simon->GetJumpingState());
	}
}
void WalkingState::Crouch()
{
	simon->SetSpeedX(0);
	simon->SetIsCrouching(true);
	simon->SetState(simon->GetCrouchingState());
}
void WalkingState::Update(DWORD dt)
{
	State::Update(dt);
}
void WalkingState::Render()
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

	simon->GetAnimationsList()[SIMON_ANI_WALKING]->Render(spriteData);
}
