#include "Card.h"
#include "Tools.h"

void Card::executeCard()
{
	cout << "카드 " << name_ << "사용 !" << '\n';
	(*executeFunc_)();
}
