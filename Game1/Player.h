#pragma once
#include "Tools.h"
#include "Pokemon.h"

class Player
{
protected:
	string name_;
	Pokemon unit_;

public:
	Player() : name_(""), unit_(Pokemon()) {}
	Player(string name) : name_(name) {}

	string getName() { return name_; }
	void setName(string name) { name_ = name; }
	void selectUnit(Pokemon unit) { unit_ = unit; }

	Pokemon& getUnit() { return unit_; }
	const Pokemon& getUnit() const { return unit_; }

	virtual void selectCardsForStage() = 0;
	virtual void executeCurrentCard() = 0;
};

