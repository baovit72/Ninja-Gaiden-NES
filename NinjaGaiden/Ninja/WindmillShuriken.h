#pragma once
#include"Subweapon.h"
#include"Ninja.h"

class WindmillShuriken : public Subweapon
{
private:
	static Animation * animation;

public:
	WindmillShuriken();
	~WindmillShuriken();
	void LoadResources() override;
	void ResetAnim() override { this->animation->Reset(); }

	int GetWidth() { return SUBWEAPON_SHURIKEN_SPRITE_WIDTH; }
	int GetHeight() { return SUBWEAPON_SHURIKEN_SPRITE_HEIGHT; }

	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};