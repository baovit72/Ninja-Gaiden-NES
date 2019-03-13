#include "WalkingState.h"

WalkingState::WalkingState(Ninja * ninja)
{
	this->ninja = ninja;
}
void WalkingState::Idle()
{
	ninja->SetSpeedX(0);

	ninja->SetState(ninja->GetIdleState());
}
void WalkingState::Attack()
{
	ninja->SetSpeedX(0);
	ninja->SetState(ninja->GetAttackingState());
}
void WalkingState::Walk()
{
	ninja->SetSpeedX(NINJA_WALKING_SPEED * (ninja->IsLeft() ? -1 : 1));
}
void WalkingState::Throw()
{
	ninja->SetSpeedX(0);
	ninja->SetState(ninja->GetThrowingState());
}
void WalkingState::Jump()
{
	if (ninja->IsGrounded())
	{
		ninja->SetIsGrounded(false);
		ninja->SetSpeedY(NINJA_JUMP_SPEED_Y);
		ninja->SetState(ninja->GetJumpingState());
	}
}
void WalkingState::Crouch()
{
	ninja->SetSpeedX(0);
	ninja->SetIsCrouching(true);
	ninja->SetState(ninja->GetCrouchingState());
}
void WalkingState::Update(DWORD dt)
{
	State::Update(dt);
}
void WalkingState::Render()
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

	ninja->GetAnimationsList()[NINJA_ANI_WALKING]->Render(spriteData);
}
