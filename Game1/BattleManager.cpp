#include "BattleManager.h"

#define _CONSOLE 1

extern void CallDrawWpfMapFromNative(const std::vector<std::vector<std::string>>& paths,
	int playerCurrentHp,
	int playerMaxHp,
	int computerCurrentHp,
	int computerMaxHp,
	std::string sound_path);

void BattleManager::init()
{
	isBattleEnd_ = false;
	currentTurn_ = 0;

	Position playerPos = humanPlayer_->getPokemon().getPos();
	Position compPos = computerPlayer_->getPokemon().getPos();

	map_[playerPos.y][playerPos.x] = &humanPlayer_->getPokemon();
	map_[compPos.y][compPos.x] = &computerPlayer_->getPokemon();

	//imageHash_[ImageName::BLANK] = "";
	//imageHash_[ImageName::PIKA] = "pika.png";
	//imageHash_[ImageName::PAI] = "pai.png";
	//imageHash_[ImageName::KKO] = "kko.png";
	//imageHash_[ImageName::NAO] = "nao.png";
	//imageHash_[ImageName::MAJ] = "maj.png";
	//imageHash_[ImageName::TTO] = "tto.png";
}

void BattleManager::executeBattle()
{
	//battle loop logic
	lastResult_ = BattleResult::NONE;
	while (true) {
		system("cls");
		printMap();
		selectCardsForStage();
		vector<Position> tmpPos;

#if _CONSOLE
		for (int i = 0; i < 3; i++) {
			// Player's turn
			tmpPos = humanPlayer_->executeCard(map_, humanCardList_[i]);
			Card tmp = humanPlayer_->getPokemon().getCards()[humanCardList_[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Player");
			if (!computerPlayer_->getPokemon().isAlive()) {
				lastResult_ = BattleResult::PLAYER_WIN;
				system("cls");
				Sleep(2000);
				return; // End battle, GameManager handle next stage
			}
			computerPlayer_->getPokemon().setShield(false);

			// Computer's turn
			tmpPos = computerPlayer_->executeCard(map_, computerCardList[i]);
			tmp = computerPlayer_->getPokemon().getCards()[computerCardList[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Computer");
			if (!humanPlayer_->getPokemon().isAlive()) {
				lastResult_ = BattleResult::COMPUTER_WIN;
				system("cls");
				Sleep(2000);
				return;
			}
			humanPlayer_->getPokemon().setShield(false);
		}
#else
		for (int i = 0; i < 3; i++) {
			// Player's turn
			tmpPos = humanPlayer_->executeCard(map_, humanCardList_[i]);
			Card tmp = humanPlayer_->getPokemon().getCards()[humanCardList_[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Player");
			if (!computerPlayer_->getPokemon().isAlive()) {
				lastResult_ = BattleResult::PLAYER_WIN;
				system("cls");
				Sleep(2000);
				return; // End battle, GameManager handle next stage
			}

			// Computer's turn
			tmpPos = computerPlayer_->executeCard(map_, computerCardList[i]);
			tmp = computerPlayer_->getPokemon().getCards()[computerCardList[i]];
			showEffect(tmpPos, tmp.getType(), tmp.getName(), "Computer");
			if (!humanPlayer_->getPokemon().isAlive()) {
				lastResult_ = BattleResult::COMPUTER_WIN;
				system("cls");
				Sleep(2000);
				return;
			}
		}
#endif

	}
}

void BattleManager::selectCardsForStage()
{
	//Collect all available cards
	const auto& allHumanCards = humanPlayer_->getPokemon().getCards();
	std::vector<std::string> allAvailableCardNames;
	for (const auto& card : allHumanCards) {
		allAvailableCardNames.push_back(card.getName());
	}

	CallShowAvailableCardsFromNative(allAvailableCardNames);
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
	vector<vector<string>> paths = vector<vector<string>>(MAX_Y, vector<string>(MAX_X));

	char effect;
	switch (cardType) {
	case CardType::ATTACK:
		if (userName == "Player") effect = 'X';
		else effect = '+';
		break;
	case CardType::MOVE:
		system("cls");
		printMap();
		cout << "<<<<<<<<< " << userName << ' ' << effectName << " >>>>>>>>>";
		Sleep(1000);
		return;
	case CardType::HEAL:
		if (userName == "Player")
			effect = 'H';
		else
			effect = 'h';
		break;
	case CardType::SHIELD:
		if (userName == "Player")
			effect = 'S';
		else
			effect = 's';
		break;
	default:
		effect = '0';
		break;
	}

	// 원하시는 대로 지우셔도댐
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
			else if (compPos.y == y && compPos.x == x) {
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

	Pokemon playerPokemon = humanPlayer_->getPokemon();
	Pokemon compPokemon = computerPlayer_->getPokemon();

	
	system("cls");
	printMap(effectMap);
	drawWpfMap(effectMap, cardType, userName);
	cout << "!!!!!!! " << userName << ' ' << effectName << "!!!!!!! \n";

	Sleep(3000);
	system("cls");
	printMap(effectMapBlank);
	cout << "!!!!!!! " << userName << ' ' << effectName << "!!!!!!! \n";
	Sleep(500);


	system("cls");
	printMap();
}

void BattleManager::printMap(vector<vector<char>> effectMap)
{
	drawWpfMap();
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << humanPlayer_->getPokemon().getName() << " HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << computerPlayer_->getPokemon().getName() << " HP: " << computerHp << " / " << computerMaxHp << "\n";

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			cout << effectMap[y][x] << ' ';
		}
		cout << '\n';
	}
}

void BattleManager::drawWpfMap(vector<vector<char>> effectMap, CardType cardType, string userName) {
	//effect type -> player, coomputer, heal, shield, etc...

	vector<vector<string>> paths = vector<vector<string>>(MAX_Y, vector<string>(MAX_X));

	Pokemon playerPokemon = humanPlayer_->getPokemon();
	Pokemon compPokemon = computerPlayer_->getPokemon();

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {

			if (map_[y][x] == nullptr) {
				if (effectMap[y][x] == 'X') {
					paths[y][x] = "../../../../Image/" + playerPokemon.getName() +"_Effect" + ".png";
				}
				else if (effectMap[y][x] == '+') {
					paths[y][x] = "../../../../Image/" + compPokemon.getName() + "_Effect" + ".png";
				}
				else {
					paths[y][x] = "";
				}
				continue;
			}
			else {
				string className = typeid(*map_[y][x]).name();
				string seat = className.substr(6);
				if ((effectMap[y][x] == 'X') && (seat != playerPokemon.getName())) {
					if (compPokemon.getShield() == true) 
						paths[y][x] = "../../../../Image/" + compPokemon.getName() + "_Shield" + ".png";
					else 
						paths[y][x] = "../../../../Image/" + compPokemon.getName() + "_Attacked" + ".png";
				}
				else if ((effectMap[y][x] == '+') &&(seat != compPokemon.getName())) {
					if (playerPokemon.getShield() == true)
						paths[y][x] = "../../../../Image/" + playerPokemon.getName() + "_Shield" + ".png";
					else 
						paths[y][x] = "../../../../Image/" + playerPokemon.getName() + "_Attacked" + ".png";
				}
				else if (effectMap[y][x] == 'H'){
					paths[y][x] = "../../../../Image/" + playerPokemon.getName() + "_Heal" + ".png";
				}
				else if (effectMap[y][x] == 'h') {
					paths[y][x] = "../../../../Image/" + compPokemon.getName() + "_Heal" + ".png";
				}
				else if (effectMap[y][x] == 'S') {
					paths[y][x] = "../../../../Image/" + playerPokemon.getName() + "_Shield" + ".png";
				}
				else if (effectMap[y][x] == 's') {
					paths[y][x] = "../../../../Image/" + compPokemon.getName() + "_Shield" + ".png";
				}
				else {
					if ((cardType == CardType::ATTACK) && (userName == "Player") && (map_[y][x]->getName() == playerPokemon.getName()))
						paths[y][x] = "../../../../Image/" + seat + "_Attack" + ".png";
					else if ((cardType == CardType::ATTACK) && (userName == "Computer") && (map_[y][x]->getName() == compPokemon.getName()))
						paths[y][x] = "../../../../Image/" + seat + "_Attack" + ".png";
					else 
						paths[y][x] = "../../../../Image/" + seat + ".png";
					
				}
				//string className = typeid(*map_[y][x]).name();
				//paths[y][x] = "../../../../Image/" + className.substr(6) + ".png";
			}

			//cout <<"y: " << y << " x: " << x << " path: " << paths[y][x] << endl;
		}
	}
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << humanPlayer_->getPokemon().getName() << " HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << computerPlayer_->getPokemon().getName() << " HP: " << computerHp << " / " << computerMaxHp << "\n";


	CallDrawWpfMapFromNative(paths, playerHp, playerMaxHp, computerHp, computerMaxHp, "../../../../Sound/background.wav");
	//CallDrawWpfMapFromNative(paths);
}

void BattleManager::drawWpfMap()
{
	vector<vector<string>> paths = vector<vector<string>>(MAX_Y, vector<string>(MAX_X));

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			
			if (map_[y][x] == nullptr) {
				paths[y][x] = "";
				continue;
			}
			else {

			}
			
			string className = typeid(*map_[y][x]).name();
			

			paths[y][x] = "../../../../Image/" + className.substr(6) + ".png";
			//cout <<"y: " << y << " x: " << x << " path: " << paths[y][x] << endl;
		}
	}

	//CallDrawWpfMapFromNative(paths);
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << humanPlayer_->getPokemon().getName() << " HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << computerPlayer_->getPokemon().getName() << " HP: " << computerHp << " / " << computerMaxHp << "\n";


	CallDrawWpfMapFromNative(paths, playerHp, playerMaxHp, computerHp, computerMaxHp, "../../../../Sound/background.wav");
}

void BattleManager::printMap()
{
	drawWpfMap();
	int playerHp = humanPlayer_->getPokemon().getHp();
	int computerHp = computerPlayer_->getPokemon().getHp();
	int playerMaxHp = humanPlayer_->getPokemon().getMaxHp();
	int computerMaxHp = computerPlayer_->getPokemon().getMaxHp();

	cout << humanPlayer_->getPokemon().getName() << " HP: " << playerHp << " / " << playerMaxHp << "\n";
	cout << computerPlayer_->getPokemon().getName() << " HP: " << computerHp << " / " << computerMaxHp << "\n";

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