#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
	HumanPlayer() : Player() {}
	HumanPlayer(string name) : Player(name) {}

	void selectCardsForStage() override;
	void executeCurrentCard() override;
};

