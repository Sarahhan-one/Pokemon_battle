#pragma once
#include "Tools.h"

class Card
{
private:
	string name;
	int powerPoint_;

public:
	Card(int powerPoint) : powerPoint_(powerPoint) {}

	int getPowerPoint() const { return powerPoint_; }

	virtual void executeCard();
};

