#include "JumpingState.h"


JumpingState::JumpingState(Ninja * ninja)
{
	this->ninja = ninja;
}
void JumpingState::Idle()
{
	
}
void JumpingState::Attack()
{
	ninja->SetState(ninja->GetAttackingState());
}
void JumpingState::Walk()
{

}
void JumpingState::Throw()
{
	ninja->SetState(ninja->GetThrowingState());
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
	//Lấy Jump and Slash
	if (this->JumpnSlash == NULL) {
		vector<Subweapon *> subweapons = ninja->GetSubweapon();
		for (int i = 0; i < subweapons.size(); i++) {
			Subweapon *subweapon = subweapons.at(i);
			//Jump slash thực hiện lúc nhảy
			if (subweapon->getType() == SUBWEAPON_JUMPSLASH)
				JumpnSlash = subweapon;
		}
	}
	if (ninja->IsGrounded())
	{
		ninja->SetSpeedX(0);
		ninja->SetSpeedY(0);

		ninja->SetState(ninja->GetIdleState());
	}
}
void JumpingState::Render()
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

	ninja->GetAnimationsList()[NINJA_ANI_JUMPING]->Render(spriteData);
	//Render Jump and Slash
	if (JumpnSlash != NULL)
		JumpnSlash->Render();
}