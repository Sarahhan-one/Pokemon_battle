#pragma once
#include "../Pokemon.h"

#define PAI_HP 80

class Pairi : public Pokemon
{
private:

public:
	Pairi(Position pos) : Pokemon(PAI_HP, PAI_HP, pos)
	{
		name_ = "Pairi";
		cards_.push_back(Card("flameThrower",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->flameThrower(map);
			}));
		cards_.push_back(Card("fireBlast",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->fireBlast(map);
			}));
		cards_.push_back(Card("ember",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->ember(map);
			}));
		cards_.push_back(Card("heatWave",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->heatWave(map);
			}));
	}


	vector<Position> flameThrower(vector<vector<Pokemon*>> map);
	vector<Position> fireBlast(vector<vector<Pokemon*>> map);
	vector<Position> ember(vector<vector<Pokemon*>> map);
	vector<Position> heatWave(vector<vector<Pokemon*>> map);

};
