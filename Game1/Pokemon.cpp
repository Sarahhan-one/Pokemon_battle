#include "Pokemon.h"

bool Pokemon::isAlive() const
{
	return hp_ <= 0;
}

void Pokemon::takeAttack(int damage)
{
	hp_ -= damage;
}

void Pokemon::excuteCard(vector<vector<Pokemon*>>& map, int cardInd)
{
	cards_[cardInd].executeCard(map);
}
