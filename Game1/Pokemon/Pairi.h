#pragma once
#include "../Pokemon.h"

#define PAI_HP 80

class Pairi : public Pokemon
{
private:

public:
	Pairi(Position pos) : Pokemon(PAI_HP, PAI_HP, pos)
	{
		//cards_.push_back(Card("thunderbolt",
		//	CardType::ATTACK,
		//	[this](vector<vector<Pokemon*>>& map) -> vector<Position>&{
		//		return this->thunderbolt(map);
		//	}));
	}

};
