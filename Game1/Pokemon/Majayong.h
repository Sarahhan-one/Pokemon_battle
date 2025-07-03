#pragma once
#include "Pokemon.h"

#define MAJ_HP 80

class Majayong : public Pokemon
{
private:

public:
	Majayong(Position pos) : Pokemon(MAJ_HP, MAJ_HP, pos)
	{
		name_ = "Majayong";

	}
};

