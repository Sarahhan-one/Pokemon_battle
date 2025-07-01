#pragma once
#include "Tools.h"

class Card
{
private:
	string name;
	int powerPoint_;
	void (*executeCard_)(void);

public:
	Card(int powerPoint) : powerPoint_(powerPoint), executeCard_(nullptr) {}

	Card(int powerPoint, void (*executeCard)(void)) :powerPoint_(powerPoint), executeCard_(executeCard) {}

	int getPowerPoint() const { return powerPoint_; }
};

