#pragma once
#include "Subweapon.h"

class Knife : public Subweapon
{
	static Animation * animation;
public:
	Knife();

	void LoadResources() override;
	void ResetAnim() override { this->animation->Reset(); }


	int GetWidth() { return SUBWEAPON_KNIFE_SPRITE_WIDTH; }
	int GetHeight() { return SUBWEAPON_KNIFE_SPRITE_HEIGHT; }
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render(SpriteData spriteData) override;
	~Knife();
};

