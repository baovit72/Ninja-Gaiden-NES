#include"ClimbingState.h"

ClimbingState::ClimbingState(Ninja *ninja) {
	this->ninja = ninja;
}
void ClimbingState::Idle()
{

}
void ClimbingState::Attack()
{

}
void ClimbingState::Walk()
{

}
void ClimbingState::Throw()
{

}
void ClimbingState::Jump()
{
	this->ninja->SetState(this->ninja->GetJumpingState());
}
void ClimbingState::Crouch()
{

}
void ClimbingState::Update(DWORD dt)
{
	State::Update(dt);

}
void ClimbingState::Render() {
	SpriteData spriteData;
	spriteData.width = NINJA_SPRITE_WIDTH;
	spriteData.height = NINJA_SPRITE_HEIGHT;
	spriteData.x = ninja->GetPositionX();
	spriteData.y = ninja->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = ninja->IsLeft();
	spriteData.isFlipped = ninja->IsFlipped();
	ninja->GetAnimationsList()[NINJA_ANI_CLIMBING]->Render(spriteData);
}