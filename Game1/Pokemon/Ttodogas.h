#pragma once
#include "../Pokemon.h"
#define TTO_HP 80

class Ttodogas : public Pokemon
{
private:

public:
	Ttodogas(Position pos) : Pokemon(TTO_HP, TTO_HP, pos)
	{
		name_ = "Ttodogas";
		cards_.push_back(Card("blech",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->blech(map);
			}));

		cards_.push_back(Card("clearSmog",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->clearSmog(map);
			}));

		cards_.push_back(Card("sludge",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->sludge(map);
			}));

		cards_.push_back(Card("sludgeBomb",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->sludgeBomb(map);
			}));
	}
	vector<Position> blech(vector<vector<Pokemon*>> map);
	vector<Position> clearSmog(vector<vector<Pokemon*>> map);
	vector<Position> sludge(vector<vector<Pokemon*>> map);
	vector<Position> sludgeBomb(vector<vector<Pokemon*>> map);
};
