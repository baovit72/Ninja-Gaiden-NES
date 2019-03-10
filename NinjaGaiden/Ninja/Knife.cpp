#include "Knife.h"

Animation * Knife::animation = NULL;

Knife::Knife()
{
	type = SUBWEAPON_KNIFE;
	this->vy = 0;
	this->vx = SUBWEAPON_SPEED_X;
	if (animation == NULL)
		LoadResources();
}


Knife::~Knife()
{
	
}

void Knife::LoadResources()
{
	animation = new Animation(150);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SUBWEAPON_KNIFE_TEXTURE_COLUMNS) * SUBWEAPON_KNIFE_SPRITE_WIDTH;
		rect.right = rect.left + SUBWEAPON_KNIFE_SPRITE_WIDTH;
		rect.top = (i / SUBWEAPON_KNIFE_TEXTURE_COLUMNS) * SUBWEAPON_KNIFE_SPRITE_HEIGHT;
		rect.bottom = rect.top + SUBWEAPON_KNIFE_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SUBWEAPON_KNIFE_TEXTURE_LOCATION, rect, SUBWEAPON_KNIFE_TEXTURE_TRANS_COLOR);

		animation->AddFrame(sprite);
	}
}
//Hàm cập nhật
void Knife::Update(DWORD dt)
{
	this->x += this->vx * (isLeft ? -1 : 1) * dt;
	this->y += this->vy * dt;
}
//Hàm render
void Knife::Render(SpriteData spriteData)
{
	spriteData.width = SUBWEAPON_KNIFE_SPRITE_WIDTH;
	spriteData.height = SUBWEAPON_KNIFE_SPRITE_HEIGHT;
	spriteData.x = x;
	spriteData.y = y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = this->isLeft;

	this->animation->Render(spriteData);

}