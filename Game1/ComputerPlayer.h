#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
private:

public:
	ComputerPlayer() : Player() {}
	ComputerPlayer(string name) : Player(name) {}

	void selectCardsForStage() override;
	void executeCurrentCard() override;
};

