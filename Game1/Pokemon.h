#pragma once
#include "Tools.h"
#include "Card.h"

enum class Type {
	NORMAL, FIRE, WATER, GRASS, ELECTRIC, ICE, FIGHTING, POISON, GROUND,
	FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY
};


class Pokemon
{
protected:
	vector<Type> types_;
	vector<Card> cards_;
	int maxHp_;
	int hp_;
	Position pos_;

public:
	Pokemon()
		: maxHp_(0), hp_(0), pos_(Position()) {
	}

	Pokemon(int maxHp, int hp, Position pos)
		: maxHp_(maxHp), hp_(hp), pos_(pos) {
	}

	vector<Type> getType() const { return types_; }
	int getHp() const { return hp_; }
	Position getPos() const { return pos_; }
	void setPos(const Position pos) { pos_ = pos; }

	bool isAlive() const;
	virtual void takeAttack(const int damage);
	vector<Position>& excuteCard(vector<vector<Pokemon*>>& map, int cardInd);
};



