#include "IdleState.h"


IdleState::IdleState(Ninja * ninja)
{
	this->ninja = ninja;
}
void IdleState::Idle()
{
	//ninja->SetState(ninja->GetIdleState());
}
void IdleState::Attack()
{
	ninja->SetState(ninja->GetAttackingState());
}
void IdleState::Walk()
{
	ninja->SetSpeedX(NINJA_WALKING_SPEED * (ninja->IsLeft() ? -1 : 1));

	ninja->SetState(ninja->GetWalkingState());
}
void IdleState::Throw()
{
	ninja->SetState(ninja->GetThrowingState());
}
void IdleState::Jump()
{
	if (ninja->IsGrounded())
	{
		ninja->SetIsGrounded(false);
		ninja->SetSpeedY(NINJA_JUMP_SPEED_Y);
		ninja->SetState(ninja->GetJumpingState());
	}
}
void IdleState::Crouch()
{
	ninja->SetIsCrouching(true);
	ninja->SetState(ninja->GetCrouchingState());
}
void IdleState::Update(DWORD dt)
{
	State::Update(dt);
}
void IdleState::Render()
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

	ninja->GetAnimationsList()[NINJA_ANI_IDLE]->Render(spriteData);
}
