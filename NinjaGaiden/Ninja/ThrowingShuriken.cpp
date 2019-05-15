#include"ThrowingShuriken.h"
Animation * ThrowingShuriken::animation = NULL;

ThrowingShuriken::ThrowingShuriken( )
{ 
	type = SUBWEAPON_THROWINGSHURIKEN;
	this->vy = 0;
	this->vx = SUBWEAPON_SPEED_X;
	if (animation == NULL)
		LoadResources();
}


ThrowingShuriken::~ThrowingShuriken()
{

}

void ThrowingShuriken::LoadResources()
{
	animation = new Animation(80);
	for (int i = 0; i < 2; i++)
	{
		RECT rect;
		rect.left = (i % SUBWEAPON_SHURIKEN_TEXTURE_COLUMNS) * SUBWEAPON_SHURIKEN_SPRITE_WIDTH;
		rect.right = rect.left + SUBWEAPON_SHURIKEN_SPRITE_WIDTH;
		rect.top = (i / SUBWEAPON_SHURIKEN_TEXTURE_COLUMNS) * SUBWEAPON_SHURIKEN_SPRITE_HEIGHT;
		rect.bottom = rect.top + SUBWEAPON_SHURIKEN_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SUBWEAPON_SHURIKEN_TEXTURE_LOCATION, rect, SUBWEAPON_SHURIKEN_TEXTURE_TRANS_COLOR);

		animation->AddFrame(sprite);
	}
}
//Hàm cập nhật
void ThrowingShuriken::Update(DWORD dt)
{
	this->x += this->vx * (isLeft ? -1 : 1) * dt;
	this->y += this->vy*dt;
	 
}
//Hàm render
void ThrowingShuriken::Render()
{
	SpriteData spriteData;
	spriteData.width = SUBWEAPON_SHURIKEN_SPRITE_WIDTH;
	spriteData.height = SUBWEAPON_SHURIKEN_SPRITE_HEIGHT;
	spriteData.x = x;
	spriteData.y = y;
	spriteData.scale = 0.7;
	spriteData.angle = 0;
	spriteData.isFlipped = this->isLeft;

	this->animation->Render(spriteData);

}