#pragma once
#include "../Pokemon.h"

#define NAO_HP 100

class Naong : public Pokemon
{
private:

public:
	Naong(Position pos) : Pokemon(NAO_HP, NAO_HP, pos)
	{
		name_ = "Naong";
	}
};

