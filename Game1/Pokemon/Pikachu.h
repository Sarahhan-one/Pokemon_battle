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
		cards_.push_back(Card("thunderbolt", [this](vector<vector<Pokemon*>>& map) {
			this->thunderbolt(map);
			}));
	}

	void thunderbolt(vector<vector<Pokemon*>>& map);
};

