#pragma once
#include "GameObject.h"
#include "Constants.h"

class Subweapon : public GameObject
{
protected:
	int type;
public:
	virtual void LoadResources() = 0;

	bool IsLeft() { return isLeft; }
	void TurnLeft() { isLeft = true; }
	void TurnRight() { isLeft = false; }
	virtual void ResetAnim() = 0;

	void SetThrownPosition(float x, float y, bool isCrouching);
	void SetType(int type) { this->type = type; }

	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(this->x, this->y); }
	//Hàm cập nhật
	virtual void Update(DWORD dt) = 0;
	//Hàm render
	virtual void Render(SpriteData spriteData) = 0;
};

