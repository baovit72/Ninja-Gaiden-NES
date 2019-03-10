#include "Subweapon.h"

void Subweapon::SetThrownPosition(float x, float y, bool isCrouching)
{
	this->x = (isLeft ? x : x + 20);
	if (isCrouching)
		this->y = y + 15 + 16.5f;
	else
		this->y = y + 15;
}