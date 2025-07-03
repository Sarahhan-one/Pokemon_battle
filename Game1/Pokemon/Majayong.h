#pragma once
#include "../Pokemon.h"

#define MAJ_HP 80

class Majayong : public Pokemon
{
private:

public:
	Majayong(Position pos) : Pokemon(MAJ_HP, MAJ_HP, pos)
	{
		name_ = "Majayong";
		cards_.push_back(Card("heal",
			CardType::HEAL,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->heal(map);
			}));
		cards_.push_back(Card("shield",
			CardType::SHIELD,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->shield(map);
			}));
	}

	vector<Position> heal(vector<vector<Pokemon*>> map);
	vector<Position> shield(vector<vector<Pokemon*>> map);
};

