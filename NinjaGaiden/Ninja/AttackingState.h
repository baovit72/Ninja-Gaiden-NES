#pragma once
#include "State.h"
#include "Ninja.h"

class AttackingState : public State
{
public:
	AttackingState(Ninja * ninja);
	void Idle();
	void Attack();
	void Walk();
	void Throw();
	void Jump();
	void Crouch();
	void Update(DWORD dt);
	void Render();
};
