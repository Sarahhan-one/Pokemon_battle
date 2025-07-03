#pragma once
#include "../Pokemon.h"

#define NAO_HP 100

class Naong : public Pokemon
{
private:

public:
	Naong(Position pos) : Pokemon(NAO_HP, NAO_HP, pos)
	{
		name_ = "Naong";
		cards_.push_back(Card("slash",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->slash(map);
			}));

		cards_.push_back(Card("scratch",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->scratch(map);
			}));

		cards_.push_back(Card("furySwipes",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->furySwipes(map);
			}));

		cards_.push_back(Card("playRough",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->playRough(map);
			}));
	}

	vector<Position> slash(vector<vector<Pokemon*>> map);
	vector<Position> scratch(vector<vector<Pokemon*>> map);
	vector<Position> furySwipes(vector<vector<Pokemon*>> map);
	vector<Position> playRough(vector<vector<Pokemon*>> map);
	
};
