#pragma once
#include "../Pokemon.h"

// hp: 100
#define PIKA_HP 100

class Pikachu : public Pokemon
{
private:

public:
	Pikachu(Position pos) : Pokemon(PIKA_HP, PIKA_HP, pos) 
	{
		cards_.push_back(Card("thunderbolt", 
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position>&{
				return this->thunderbolt(map);
			}));
	}

	vector<Position>& thunderbolt(vector<vector<Pokemon*>>& map);
};

