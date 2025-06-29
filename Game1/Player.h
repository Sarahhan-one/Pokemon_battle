#pragma once
#include "Tools.h"
#include "Unit.h"

class Player
{
protected:
	string name_;
	Unit unit_;

public:
	Player() : name_(""), unit_(Unit()) {}
	Player(string name) : name_(name) {}

	string getName() { return name_; }
	void setName(string name) { name_ = name; }
	void selectUnit(Unit unit) { unit_ = unit; }

	virtual void selectCardsForStage() = 0;
	virtual void executeCurrentCard() = 0;
};

