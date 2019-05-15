#include"FireWheel.h"
Animation * FireWheel::animation = NULL;
FireWheel::FireWheel() {
	type = SUBWEAPON_FIREWHEEL;
	if (animation == NULL)
		LoadResources();
}
FireWheel::~FireWheel() {

}
void FireWheel::LoadResources()
{
	animation = new Animation(130);
	for (int i = 0; i < 3; i++)
	{
		RECT rect;
		rect.left = (i % SUBWEAPON_FIREWHEEL_TEXTURE_COLUMNS) * SUBWEAPON_FIREWHEEL_SPRITE_WIDTH;
		rect.right = rect.left + SUBWEAPON_FIREWHEEL_SPRITE_WIDTH;
		rect.top = (i / SUBWEAPON_FIREWHEEL_TEXTURE_COLUMNS) * SUBWEAPON_FIREWHEEL_SPRITE_HEIGHT;
		rect.bottom = rect.top + SUBWEAPON_FIREWHEEL_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(SUBWEAPON_FIREWHEEL_TEXTURE_LOCATION, rect, SUBWEAPON_FIREWHEEL_TEXTURE_TRANS_COLOR);

		animation->AddFrame(sprite);
	}
}

//Hàm cập nhật
void FireWheel::Update(DWORD dt)
{
	Ninja *ninja;
	ninja = Ninja::GetInstance();
	int DeltaX = -5;
	 
	this->x = ninja->GetPositionX() + DeltaX;
	this->y = ninja->GetPositionY() + 10;

}
//Hàm render
void FireWheel::Render()
{
	SpriteData spriteData;
	spriteData.width = SUBWEAPON_FIREWHEEL_SPRITE_WIDTH;
	spriteData.height = SUBWEAPON_FIREWHEEL_SPRITE_HEIGHT;
	spriteData.x = x;
	spriteData.y = y;
	spriteData.scale = 1.5;
	spriteData.angle = 0;
	spriteData.isFlipped = FALSE;

	this->animation->Render(spriteData);

}