#pragma once
#include "Unit.h"

class ZergUnit : public Unit
{
public:

	void takeDamage() override;
	void endTurn();
	virtual void skill1();
	virtual void skill2();
	virtual void skill3();
	virtual void skill4();
};

