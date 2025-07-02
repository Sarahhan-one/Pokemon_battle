#include "BattleManager.h"

void BattleManager::init()
{
	isBattleEnd_ = false;
	currentTurn_ = 0;

	Position playerPos = humanPlayer_->getPokemon().getPos();
	Position compPos = computerPlayer_->getPokemon().getPos();

	map_[playerPos.y][playerPos.x] = &humanPlayer_->getPokemon();
	map_[compPos.y][compPos.x] = &computerPlayer_->getPokemon();
}

void BattleManager::executeBattle()
{
	//battle loop logic
	while (true) {
		system("cls");
		printMap();
		selectCardsForStage();
		vector<Position> tmpPos;
		
		for (int i = 0; i < 3; i++) {
			tmpPos = humanPlayer_->executeCard(map_, humanCardList_[i]);
			Card tmp = humanPlayer_->getPokemon().getCards()[humanCardList_[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Player");
			tmpPos = computerPlayer_->executeCard(map_, computerCardList[i]);
			tmp = computerPlayer_->getPokemon().getCards()[computerCardList[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Computer");
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

void BattleManager::showEffect(vector<Position> poss, CardType cardType, string effectName, string userName)
{

	char effect;
	switch (cardType) {
	case CardType::ATTACK:
		effect = 'X';
		break;
	case CardType::MOVE:
		system("cls");
		printMap();
		cout << "<<<<<<<<< " << userName << " Move >>>>>>>>>";
		Sleep(1000);
		return;
	default:
		effect = '0';
		break;
	}
	
	if (poss.size() == 0) {
		return;
	}

	Position playerPos = humanPlayer_->getPokemon().getPos();
	Position compPos = computerPlayer_->getPokemon().getPos();

	vector<vector<char>> effectMap(MAX_Y, vector<char>(MAX_X));
	vector<vector<char>> effectMapBlank(MAX_Y, vector<char>(MAX_X));
	char curOut;
	char curOutBlank;
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (playerPos.y == y && playerPos.x == x) {
				curOut = 'P';
				curOutBlank = curOut;
			}
			else if (playerPos.y == y && compPos.x == x) {
				curOut = 'C';
				curOutBlank = curOut;
			}
			else {
				curOut = '0';
				curOutBlank = curOut;
			}
			
			// 중복 할당이지만 성능 및 구현 상 문제 없음
			for (Position pos : poss) {
				if (pos.y == y && pos.x == x) {
					cout << effect;
					curOut = effect;
					curOutBlank = ' ';
					break;
				}
			}

			effectMap[y][x] = curOut;
			effectMapBlank[y][x] = curOutBlank;
		}
	}

	for (int i = 0; i < 3; i++) {

		system("cls");
		printMap(effectMap);
		cout << "!!!!!!! " << userName << ' ' << effectName << "!!!!!!! \n";
		Sleep(500);
		system("cls");
		printMap(effectMapBlank);
		cout << "!!!!!!! " << userName << ' ' << effectName << "!!!!!!! \n";
		Sleep(500);
	}

	system("cls");
	printMap();

}

void BattleManager::printMap(vector<vector<char>> effectMap)
{
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << "Player HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << "Computer HP: " << computerHp << " / " << computerMaxHp << "\n";

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			cout << effectMap[y][x] << ' ';
		}
		cout << '\n';
	}
}

void BattleManager::printMap()
{
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << "Player HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << "Computer HP: " << computerHp << " / " << computerMaxHp << "\n";

	Position playerPos = humanPlayer_->getPokemon().getPos();
	Position compPos = computerPlayer_->getPokemon().getPos();

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (playerPos.y == y && playerPos.x == x) {
				cout << "P "; //player
			}
			else if (compPos.y == y && compPos.x == x) {
				cout << "C "; //computer
			}
			else {
				cout << "0 ";
			}
		}
		cout << '\n';
	}
}