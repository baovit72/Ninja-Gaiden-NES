#include "Whip.h"
#include "Ninja.h"

vector<Animation *> Whip::animations = vector<Animation *>();
Whip::Whip()
{
	type = WHIP_NORMAL;
	LoadResources();
}
void Whip::LoadResources()
{
	// 0
	Animation * anim = new Animation(150);
	for (int i = 0; i < 3; i++)
	{
		RECT rect;
		rect.left = (i % WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_WIDTH;
		rect.right = rect.left + WHIP_SPRITE_WIDTH;
		rect.bottom = (i / WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_HEIGHT;
		rect.top = rect.bottom + WHIP_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(WHIP_TEXTURE_LOCATION, rect, WHIP_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 1
	anim = new Animation(150);
	for (int i = 3; i < 6; i++)
	{
		RECT rect;
		rect.left = (i % WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_WIDTH;
		rect.right = rect.left + WHIP_SPRITE_WIDTH;
		rect.bottom = (i / WHIP_TEXTURE_COLUMNS) * WHIP_SPRITE_HEIGHT;
		rect.top = rect.bottom + WHIP_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(WHIP_TEXTURE_LOCATION, rect, WHIP_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// 2
	anim = new Animation(150);
	for (int i = 7; i < 16; i++)
	{
		if (i == 7 || i == 11 || i == 15)
		{
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
void Whip::SetPosition(float x, float y, bool isCrouching)
{
	this->x = x - 90.0f;
	if (isCrouching)
		this->y = y + 16.5f;
	else
		this->y = y;
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
//Hàm render
void Whip::Render(SpriteData spriteData)
{
	spriteData.width = WHIP_SPRITE_WIDTH;
	spriteData.height = WHIP_SPRITE_HEIGHT;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = this->isLeft;

	this->animations[type]->Render(spriteData);
}
Whip::~Whip()
{

}