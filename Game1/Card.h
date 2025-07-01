#pragma once
#include "Tools.h"

class Card
{
private:
	string name_;
	void (*executeFunc_)(void);

public:
	Card(string name, void (*executeFunc)(void)) : name_(), executeFunc_(executeFunc) {}

	string getName() const { return name_; }
	void executeCard();
};

