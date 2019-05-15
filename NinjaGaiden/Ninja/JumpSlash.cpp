#include"JumpSlash.h"
Animation * JumpSlash::animation = NULL;
JumpSlash::JumpSlash() {
	type = SUBWEAPON_JUMPSLASH;
	if (animation == NULL)
		LoadResources();
}
JumpSlash::~JumpSlash() {

}
void JumpSlash::LoadResources()
{
	animation = new Animation(130);
	 
	for (int i = 15; i < 19; i++)
	{
		RECT rect;
		rect.left = (i % SUBWEAPON_JUMPSLASH_TEXTURE_COLUMNS) * SUBWEAPON_JUMPSLASH_SPRITE_WIDTH;
		rect.right = rect.left + SUBWEAPON_JUMPSLASH_SPRITE_WIDTH;
		rect.top = (i / SUBWEAPON_JUMPSLASH_TEXTURE_COLUMNS) * SUBWEAPON_JUMPSLASH_SPRITE_HEIGHT;
		rect.bottom = rect.top + SUBWEAPON_JUMPSLASH_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SUBWEAPON_JUMPSLASH_TEXTURE_LOCATION, rect, SUBWEAPON_JUMPSLASH_TEXTURE_TRANS_COLOR);

		animation->AddFrame(sprite);
	}
}

//Hàm cập nhật
void JumpSlash::Update(DWORD dt)
{
	Ninja *ninja;
	ninja = Ninja::GetInstance();
	int DeltaX = -5;
	this->isLeft = ninja->IsFlipped();
	if (isLeft)
		DeltaX = -20;

	this->x = ninja->GetPositionX() + DeltaX;
	this->y = ninja->GetPositionY() + 5;

}
//Hàm render
void JumpSlash::Render()
{
	SpriteData spriteData;
	spriteData.width = SUBWEAPON_FIREWHEEL_SPRITE_WIDTH;
	spriteData.height = SUBWEAPON_FIREWHEEL_SPRITE_HEIGHT;
	spriteData.x = x;
	spriteData.y = y;
	spriteData.scale = 1.2;
	spriteData.angle = 0;
	spriteData.isFlipped = isLeft;

	this->animation->Render(spriteData);

}