#include "Whip.h"
#include "Ninja.h"

vector<Animation *> Whip::animations = vector<Animation *>();
Whip::Whip(Ninja *ninja)
{
	type = WHIP_NORMAL;
	this->ninja = ninja;
	LoadResources();
}
void Whip::LoadResources()
{
	// 0  - WHIP NORMAL
	Animation * anim = new Animation(120);
	RECT rect;
	rect.left = 0;
	rect.right = 0;
	rect.bottom = 0;
	rect.top = 0;
	Sprite * sprite = new Sprite(WHIP_TEXTURE_LOCATION, rect, WHIP_TEXTURE_TRANS_COLOR);

	anim->AddFrame(sprite);

	for (int i = 12; i < 15; i++)
	{
		if (i == 12 || i == 14) {
			RECT rect;
			rect.left = (i % WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_WIDTH;
			rect.right = rect.left + WHIP_SPRITE_WIDTH;
			rect.bottom = (i / WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_HEIGHT;
			rect.top = rect.bottom + WHIP_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(WHIP_TEXTURE_LOCATION, rect, WHIP_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);

		}
	}
	animations.push_back(anim);



}


void Whip::ResetAnim()
{
	for (int i = 0; i < animations.size(); i++)
		animations[i]->Reset();
}
void Whip::TurnLeft()
{
	isLeft = true;
}
void Whip::TurnRight()
{
	isLeft = false;
}
//Hàm cập nhật
void Whip::Update(DWORD dt)
{

}
// -> Cập nhật lại vị trí của whip theo ninja
void Whip::UpdatePosition()
{
	int deltaX = 26;
	if (ninja->IsFlipped()) { 
		deltaX = -26;
	}
	this->isFlipped = ninja->IsFlipped();
	this->x = ninja->GetPositionX() + deltaX;
	if (ninja->IsCrouching())
		this->y = ninja->GetPositionY() - 40;
	else
		this->y = ninja->GetPositionY() - 35;



}
//Hàm render
void Whip::Render()
{
	this->UpdatePosition();
	SpriteData spriteData;
	spriteData.width = WHIP_SPRITE_WIDTH;
	spriteData.height = WHIP_SPRITE_HEIGHT;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isFlipped = this->isFlipped;

	this->animations[type]->Render(spriteData);
}
Whip::~Whip()
{

}