#pragma once
#include "../Pokemon.h"

#define NAO_HP 100

class Naong : public Pokemon
{
private:

public:
	Naong(Position pos) : Pokemon(NAO_HP, NAO_HP, pos)
	{
		//cards_.push_back(Card("thunderbolt",
		//	CardType::ATTACK,
		//	[this](vector<vector<Pokemon*>>& map) -> vector<Position>&{
		//		return this->thunderbolt(map);
		//	}));
		name_ = "Naong";
	}
};
