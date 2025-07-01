#include "Pokemon.h"

bool Pokemon::isAlive() const
{
	return hp_ <= 0;
}

void Pokemon::takeAttack(int damage)
{
	hp_ -= damage;
}

vector<Position>& Pokemon::excuteCard(vector<vector<Pokemon*>>& map, int cardInd)
{
	return cards_[cardInd].executeCard(map);
}
