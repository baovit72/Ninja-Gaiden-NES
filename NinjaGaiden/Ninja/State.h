#pragma once
#include "d3d9.h"

class Ninja;
class State
{
protected:
	Ninja * ninja;
public:
	virtual void Idle() = 0;
	virtual void Attack() = 0;
	virtual void Walk() = 0;
	virtual void Throw() = 0;
	virtual void Jump() = 0;
	virtual void Crouch() = 0;
	virtual void Update(DWORD dt);
	virtual void Render();
};

