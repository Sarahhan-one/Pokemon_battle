#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
private:

public:
	ComputerPlayer() : Player() {}
	ComputerPlayer(string name) : Player(name) {}

	vector<int> selectCardsForStage() override;
	vector<Position> executeCard(vector<vector<Pokemon*>>& map, int cardInd);
};

