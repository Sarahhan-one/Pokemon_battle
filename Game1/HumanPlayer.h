#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
	HumanPlayer() : Player() {}
	HumanPlayer(string name) : Player(name) {}

	vector<int> selectCardsForStage() override;
	vector<Position> executeCard(vector<vector<Pokemon*>> map, int cardInd) override;
};

