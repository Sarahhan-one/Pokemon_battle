#include "Card.h"
#include "Tools.h"
#include "Pokemon.h"

void Card::executeCard(vector<vector<Pokemon*>>& map)
{
	cout << "카드 " << name_ << "사용 !" << '\n';
	(executeFunc_)(map);
}
