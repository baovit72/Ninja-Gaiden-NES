#pragma once
#include"Subweapon.h"
#include"Ninja.h"
class FireWheel :
	public Subweapon
{
private:
	static Animation * animation;
public:
	FireWheel();
	~FireWheel();
	void LoadResources() override;
	void ResetAnim() override { this->animation->Reset(); }

	int GetWidth() { return SUBWEAPON_FIREWHEEL_SPRITE_WIDTH; }
	int GetHeight() { return SUBWEAPON_FIREWHEEL_SPRITE_HEIGHT; }

	//Cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;

};