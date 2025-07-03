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
		name_ = "Pikachu";
		cards_.push_back(Card("thunderbolt",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->thunderbolt(map);
			}));

		cards_.push_back(Card("disCharge",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->disCharge(map);
			}));

		cards_.push_back(Card("electricBall",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->electricBall(map);
			}));

		cards_.push_back(Card("spark",
			CardType::ATTACK,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->spark(map);
			}));

		cards_.push_back(Card("heal",
			CardType::HEAL,
			[this](vector<vector<Pokemon*>>& map) -> vector<Position> {
				return this->heal(map);
			}));
	}

	vector<Position> thunderbolt(vector<vector<Pokemon*>> map);
	vector<Position> disCharge(vector<vector<Pokemon*>> map);
	vector<Position> electricBall(vector<vector<Pokemon*>> map);
	vector<Position> spark(vector<vector<Pokemon*>> map);
	vector<Position> heal(vector<vector<Pokemon*>> map);
};

