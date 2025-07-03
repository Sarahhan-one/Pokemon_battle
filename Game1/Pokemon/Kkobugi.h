#pragma once
#include "../Pokemon.h"

#define KKOBU_HP 120

class Kkobugi : public Pokemon
{
private:

public:
	Kkobugi(Position pos) : Pokemon(KKOBU_HP, KKOBU_HP, pos)
	{
		name_ = "Kkobugi";
		//cards_.push_back(Card("thunderbolt",
		//	CardType::ATTACK,
		//	[this](vector<vector<Pokemon*>>& map) -> vector<Position>&{
		//		return this->thunderbolt(map);
		//	}));
	}

};
