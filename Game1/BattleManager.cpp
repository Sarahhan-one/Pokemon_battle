#include "BattleManager.h"

void BattleManager::init()
{
	battleMap_.setTile(humanPlayer_.getUnit().getPos(), 1); // 1 = character
	battleMap_.setTile(computerPlayer_.getUnit().getPos(), 2); // 2 = opponent
	isBattleEnd_ = false; 
	currentTurn_ = 0;
}

void BattleManager::selectCardsForStage()
{
	//for now, just print whose turn it is
	std::cout << "Turn: " << (currentTurn_ % 2 == 0 ? "Player" : "Opponent") << std::endl;
}

void BattleManager::executeCurrentCard()
{
	if (currentTurn_ % 2 == 0) {
		std::cout << "1. Move \n2. Attck \n";
		int action; 
		std::cin >> action;
		
		if (action == 1) {
			int x, y;
			std::cout << "new location (x, y): ";
			std::cin >> x >> y; 
			Position newPos(x, y);
			if (battleMap_.isWalkable(newPos)) {
				battleMap_.setTile(humanPlayer_.getUnit().getPos(), 0);
				humanPlayer_.getUnit().setPos(newPos);
				battleMap_.setTile(newPos, 1);
				
				
			}
		}
		if (action == 2) { //need to add battle logic
		}
	} 
	else { //opponent's turn

	}
	currentTurn_++;
}

bool BattleManager::getIsBattleEnd()
{
	return isBattleEnd_;
}

void BattleManager::setIsBattleEnd(bool isBattleEnd)
{
	isBattleEnd_ = isBattleEnd;
}
