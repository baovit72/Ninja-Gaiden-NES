#pragma once
#include "State.h"
#include "Simon.h"

class AttackingState : public State
{
public:
	AttackingState(Simon * simon);
	void Idle();
	void Attack();
	void Walk();
	void Throw();
	void Jump();
	void Crouch();
	void Update(DWORD dt);
	void Render();
};
