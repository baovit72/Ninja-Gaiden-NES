#pragma once

#include "GameObject.h"

#include "Whip.h"
#include "Knife.h"

#include "IdleState.h"
#include "WalkingState.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "AttackingState.h"
#include "ThrowingState.h"

#include "Constants.h"
class State;
class Ninja : public GameObject
{
	Ninja();
	static Ninja * __instance;

	State * idleState;
	State * walkingState;
	State * crouchingState;
	State * jumpingState;
	State * attackingState;
	State * throwingState;

	State * state;

	bool isGrounded = false;
	bool isCrouching = false;
	//Vector chứa các animations
	static vector<Animation *> animations;
	DWORD lastFrameTime;
	//Roi
	Whip * whip;
	//Vũ khí phụ
	int curSubweapon;
	static vector<Subweapon *> subweapons;
public:
	void LoadResources();
	//Hàm set
	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	void SetState(State * state);
	void SetWhip(int type) { this->whip->SetType(type); }
	//Hàm get
	static Ninja * GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	vector<Subweapon *> GetSubweapon() { return this->subweapons; }

	State * GetIdleState();
	State * GetWalkingState();
	State * GetAttackingState();
	State * GetThrowingState();
	State * GetCrouchingState();
	State * GetJumpingState();

	Whip * GetWhip() { return this->whip; }
	//Hàm trạng thái
	bool IsAttacking() { return state == attackingState || state == throwingState; }
	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }

	vector<Animation *> GetAnimationsList() { return animations; }
	//Các hàm hành động nhân vật
	void Idle();
	void Attack();
	void Walk();
	void Throw();
	void Jump();
	void Crouch();

	void CreateThrownWeapon();
	void TurnLeft();
	void TurnRight();
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};

