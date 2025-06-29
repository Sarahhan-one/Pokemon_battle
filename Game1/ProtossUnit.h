#pragma once
#include "Unit.h"

class ProtossUnit : public Unit
{
protected:
	int shield_;
	int maxShield_;

public:
	ProtossUnit(int shield, int maxShield) : shield_(shield), maxShield_(maxShield) {}

	void takeDamage() override;
	void endTurn();
	virtual void skill1();
	virtual void skill2();
	virtual void skill3();
	virtual void skill4();
};

