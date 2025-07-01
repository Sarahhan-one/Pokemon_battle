#include "BattleManager.h"

void BattleManager::init()
{
	//battleMap_.setTile(humanPlayer_.getUnit().getPos(), 1); // 1 = character
	//battleMap_.setTile(computerPlayer_.getUnit().getPos(), 2); // 2 = opponent
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
			std::cout << "new location (y, x): ";
			std::cin >> y >> x; 
			Position newPos(x, y);
			if (map_[y][x] == nullptr) {
				humanPlayer_.getPokemon().setPos(newPos);
				map_[y][x] = &humanPlayer_.getPokemon();
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

void BattleManager::printMap()
{
	for (int i = 0; i < map_[0].size(); i++) {
		for (Pokemon* cur : map_[i]) {
			if (cur == nullptr) {
				cout << 0;
			}
			else { // 포켓몬에 따라서 다르게 해야할 듯? 또는 포켓몬 넘버 부여
				cout << 1;
			}
			cout << ' ';
		}
		cout << '\n';
	}
}
