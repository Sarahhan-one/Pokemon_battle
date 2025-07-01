#pragma once
#include "Tools.h"
#include "Pokemon.h"

class Player
{
protected:
	string name_;
	Pokemon pokemon_;

public:
	Player() : name_(""), pokemon_(Pokemon()) {}
	Player(string name) : name_(name) {}

	string getName() { return name_; }
	void setName(string name) { name_ = name; }
	void selectPokemon(Pokemon pokemon) { pokemon_ = pokemon; }

	Pokemon& getPokemon() { return pokemon_; }
	const Pokemon& getPokemon() const { return pokemon_; }

	virtual void selectCardsForStage() = 0;
	virtual void executeCurrentCard() = 0;
};

