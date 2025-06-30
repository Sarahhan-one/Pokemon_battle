#include "Pokemon.h"

bool Pokemon::isAlive() const
{
	return hp_ <= 0;
}

void Pokemon::takeAttack(int damage)
{
	hp_ -= damage;
}
