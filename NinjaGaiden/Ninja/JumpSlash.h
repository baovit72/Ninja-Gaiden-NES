#pragma once
#include"Subweapon.h"
#include"Ninja.h"
class JumpSlash :
public Subweapon
{
private:
	static Animation * animation;
public:
	JumpSlash();
	~JumpSlash();
	void LoadResources() override;
	void ResetAnim() override { this->animation->Reset(); }

	int GetWidth() { return SUBWEAPON_JUMPSLASH_SPRITE_WIDTH; }
	int GetHeight() { return SUBWEAPON_JUMPSLASH_SPRITE_HEIGHT; }

	//Cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;

};