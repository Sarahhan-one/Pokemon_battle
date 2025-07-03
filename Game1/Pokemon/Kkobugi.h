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
		cards_.push_back(Card("waveCrash",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->waveCrash(map);
			}));

		cards_.push_back(Card("hydroPump",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->hydroPump(map);
			}));
		cards_.push_back(Card("waterGun",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->waterGun(map);
			}));
		cards_.push_back(Card("tailWhip",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->tailWhip(map);
			}));
	}


	vector<Position> waveCrash(vector<vector<Pokemon*>> map);
	vector<Position> hydroPump(vector<vector<Pokemon*>> map);
	vector<Position> waterGun(vector<vector<Pokemon*>> map);
	vector<Position> tailWhip(vector<vector<Pokemon*>> map);

};
