#include "JumpingState.h"


JumpingState::JumpingState(Simon * simon)
{
	this->simon = simon;
}
void JumpingState::Idle()
{

}
void JumpingState::Attack()
{
	simon->SetState(simon->GetAttackingState());
}
void JumpingState::Walk()
{

}
void JumpingState::Throw()
{
	simon->SetState(simon->GetThrowingState());
}
void JumpingState::Jump()
{

}
void JumpingState::Crouch()
{

}
void JumpingState::Update(DWORD dt)
{
	State::Update(dt);
	
	if (simon->GetPositionY() >= 100)
	{
		simon->SetState(simon->GetIdleState());
	}
}
void JumpingState::Render()
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

	simon->GetAnimationsList()[SIMON_ANI_JUMPING]->Render(spriteData);
}