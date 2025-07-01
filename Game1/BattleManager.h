#pragma once
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

#define MAP_SIZE 6

class BattleManager
{
private:
	// ~_ 구조가 google, tensorflow 등의 modern c++ style 이라고 해서 사용해봤습니다.
	HumanPlayer humanPlayer_;
	ComputerPlayer computerPlayer_;
	vector<vector<Pokemon*>> map_;
	int currentTurn_;
	bool isBattleEnd_;

public:
	BattleManager() : currentTurn_(0), isBattleEnd_(false),
		humanPlayer_(HumanPlayer()), computerPlayer_(ComputerPlayer()), 
		map_(vector<vector<Pokemon*>>(MAP_SIZE, vector<Pokemon*>(MAP_SIZE))) {};

	void init();
	void selectCardsForStage();
	void executeCurrentCard();
	bool getIsBattleEnd();
	void setIsBattleEnd(bool isBattleEnd);
	
	void printMap();

	void setHumanUnit(const Pokemon& unit) { humanPlayer_.selectPokemon(unit); }
	void setComputerUnit(const Pokemon& unit) { computerPlayer_.selectPokemon(unit); }
};

