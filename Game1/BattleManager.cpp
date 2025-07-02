#include "BattleManager.h"

void BattleManager::init()
{
	isBattleEnd_ = false;
	currentTurn_ = 0;
}

void BattleManager::executeBattle()
{
	//battle loop logic
	while (true) {
		system("cls");
		printMap();
		selectCardsForStage();
		
		for (int i = 0; i < 3; i++) {

			system("cls");
			humanPlayer_->executeCard(map_, humanCardList_[i]);
			printMap();
			Sleep(1500);
			system("cls");
			computerPlayer_->executeCard(map_, computerCardList[i]);
			printMap();
			Sleep(1500);
			system("cls");
		}
	}

	Sleep(2000);
	system("cls");
	std::cout << "전투가 종료되었습니다.\n";
}

void BattleManager::selectCardsForStage()
{
	humanCardList_ = humanPlayer_->selectCardsForStage();
	computerCardList = computerPlayer_->selectCardsForStage();
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
	Position playerPos = humanPlayer_->getPokemon().getPos();
	Position compPos = computerPlayer_->getPokemon().getPos();

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (playerPos.y == y && playerPos.x == x) {
				cout << "P "; //player
			}
			else if (playerPos.y == y && compPos.x == x) {
				cout << "C "; //computer
			}
			else {
				cout << "0 ";
			}
		}
		cout << '\n';
	}
}