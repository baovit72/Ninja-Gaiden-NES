#pragma once
#include "State.h"
#include "Ninja.h"

class JumpingState : public State
{
public:
	JumpingState(Ninja * ninja);
	void Idle();
	void Attack();
	void Walk();
	void Throw();
	void Jump();
	void Crouch();
	void Update(DWORD dt);
	void Render();
};