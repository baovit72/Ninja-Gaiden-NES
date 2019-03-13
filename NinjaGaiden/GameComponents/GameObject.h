#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprite.h"
#include "Animation.h"
class GameObject
{

protected:
	//Các giá trị vị trí, tốc độ, trạng thái
	float x;
	float y;

	float vx;
	float vy;

	bool isLeft;
	bool isFlipped;
public:
	//Hàm đặt vị trí
	void SetPositionX(float x) { this->x = x; }
	void SetPositionY(float y) { this->y = y; }
	//Hàm đặt tốc độ
	void SetSpeedX(float vx) { this->vx = vx; }
	void SetSpeedY(float vy) { this->vy = vy; }

	float GetPositionX() { return this->x; }
	float GetPositionY() { return this->y; }
	float GetSpeedX() { return this->vx; }
	float GetSpeedY() { return this->vy; }

	//Hàm khởi tạo
	GameObject();
	//Hàm cập nhật
	virtual void Update(DWORD dt);
	//Hàm render
	virtual void Render();
	//Hàm hủy đối tượng
	~GameObject();
};

