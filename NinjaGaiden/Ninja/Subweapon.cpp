#include "Subweapon.h"

void Subweapon::SetThrownPosition(float x, float y, bool isCrouching)
{
	this->x = (isLeft ? x-10 : x + 20); 
	this->y = y - 5;
	
}