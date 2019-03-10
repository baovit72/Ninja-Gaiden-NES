#pragma once
#include "GameObject.h"
#include "Constants.h"

class Whip : public GameObject
{
	static vector<Animation *> animations;
	int type;
public:
	Whip();
	void LoadResources();
	void TurnLeft();
	void TurnRight();
	void ResetAnim();

	void SetPosition(float x, float y, bool isCrouching);
	void SetType(int type) { this->type = type; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(this->x, this->y); }
	//Hàm cập nhật
	void Update(DWORD dt);
	//Hàm render
	void Render(SpriteData spriteData);
	~Whip();
};

