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
	}
};