#include "IdleState.h"


IdleState::IdleState(Simon * simon)
{
	this->simon = simon;
}
void IdleState::Idle()
{
	//simon->SetState(simon->GetIdleState());
}
void IdleState::Attack()
{
	simon->SetState(simon->GetAttackingState());
}
void IdleState::Walk()
{
	simon->SetSpeedX(SIMON_WALKING_SPEED * (simon->IsLeft() ? -1 : 1));

	simon->SetState(simon->GetWalkingState());
}
void IdleState::Throw()
{
	simon->SetState(simon->GetThrowingState());
}
void IdleState::Jump()
{
	if (simon->IsGrounded())
	{
		simon->SetIsGrounded(false);
		simon->SetSpeedY(-SIMON_JUMP_SPEED_Y);
		simon->SetState(simon->GetJumpingState());
	}
}
void IdleState::Crouch()
{
	simon->SetIsCrouching(true);
	simon->SetState(simon->GetCrouchingState());
}
void IdleState::Update(DWORD dt)
{
	State::Update(dt);
}
void IdleState::Render()
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

	simon->GetAnimationsList()[SIMON_ANI_IDLE]->Render(spriteData);
}
