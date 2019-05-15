#include"WindmillShuriken.h"
Animation * WindmillShuriken::animation = NULL;

WindmillShuriken::WindmillShuriken()
{
	type = SUBWEAPON_WINDMILLSHURIKEN;
	this->vy = 0;
	this->vx = SUBWEAPON_SPEED_X;
	if (animation == NULL)
		LoadResources();
}


WindmillShuriken::~WindmillShuriken()
{

}

void WindmillShuriken::LoadResources()
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
void WindmillShuriken::Update(DWORD dt)
{
	Ninja *ninja = Ninja::GetInstance();
	//Shuriken di chuyển qua lại ninja 
	int leftBorder = ninja->GetPositionX() - 50;
	int rightBorder = ninja->GetPositionX() + 76;

	
	if (this->x >= rightBorder)
		isLeft = TRUE;
	if (this->x <= leftBorder)
		isLeft = FALSE;
	//Di chuyển shuriken 
	this->x += this->vx * (isLeft ? -1 : 1) * dt;
	this->y = Ninja::GetInstance()->GetPositionY();

}
//Hàm render
void WindmillShuriken::Render()
{
	SpriteData spriteData;
	spriteData.width = SUBWEAPON_SHURIKEN_SPRITE_WIDTH;
	spriteData.height = SUBWEAPON_SHURIKEN_SPRITE_HEIGHT;
	spriteData.x = x;
	spriteData.y = y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isFlipped = this->isLeft;

	this->animation->Render(spriteData);

}