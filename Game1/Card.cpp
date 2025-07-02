#include "Card.h"
#include "Tools.h"
#include "Pokemon.h"

vector<Position> Card::executeCard(vector<vector<Pokemon*>>& map) const
{
	return (executeFunc_)(map);
}
