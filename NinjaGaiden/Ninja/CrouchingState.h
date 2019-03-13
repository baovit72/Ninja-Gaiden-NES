#pragma once
#include "State.h"
#include "Ninja.h"

class CrouchingState : public State
{
public:
	CrouchingState(Ninja * ninja);
	void Idle();
	void Attack();
	void Walk();
	void Throw();
	void Jump();
	void Crouch();
	void Update(DWORD dt);
	void Render();
};