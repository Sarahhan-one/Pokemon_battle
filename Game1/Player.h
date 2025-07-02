#pragma once
#include "Tools.h"
#include "Pokemon.h"

class Player
{
protected:
	string name_;
	Pokemon* pokemon_;

public:
	Player() : Player("") {}
	Player(string name) : name_(name), pokemon_(nullptr) {}

	string getName() { return name_; }
	void setName(string name) { name_ = name; }
	void selectPokemon(Pokemon* const pokemon) { pokemon_ = pokemon; }

	Pokemon& getPokemon() { return *pokemon_; }

	virtual vector<int> selectCardsForStage() { return vector<int>(); }
	virtual void executeCard(vector<vector<Pokemon*>> map, int cardInd) = 0;
};

