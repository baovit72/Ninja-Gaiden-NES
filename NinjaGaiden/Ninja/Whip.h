#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Ninja.h"
class Ninja;
class Whip : public GameObject
{
private:
	Ninja *ninja;
	static vector<Animation *> animations;
	int type;
	
public:
	Whip(Ninja *ninja);
	void LoadResources();
	void TurnLeft();
	void TurnRight();
	void ResetAnim(); 
	void UpdatePosition();
	void SetType(int type) { this->type = type; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(this->x, this->y); }
	//Hàm cập nhật
	void Update(DWORD dt);
	//Hàm render
	void Render( );
	~Whip();
};

