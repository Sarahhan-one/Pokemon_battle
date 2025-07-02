#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
	HumanPlayer() : Player() {}
	HumanPlayer(string name) : Player(name) {}

	vector<int> selectCardsForStage() override;
	void executeCard(vector<vector<Pokemon*>> map, int cardInd) override;
};

