#pragma once
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "BattleMap.h"

class BattleManager
{
private:
	// ~_ 구조가 google, tensorflow 등의 modern c++ style 이라고 해서 사용해봤습니다.
	HumanPlayer humanPlayer_;
	ComputerPlayer computerPlayer_;
	BattleMap battleMap_;
	int currentTurn_;
	bool isBattleEnd_;

public:
	BattleManager() : currentTurn_(0), isBattleEnd_(false),
		humanPlayer_(HumanPlayer()), computerPlayer_(ComputerPlayer()),
		battleMap_(BattleMap(Position(10,10))) {};

	void init();
	void selectCardsForStage();
	void executeCurrentCard();
	bool getIsBattleEnd();
	void setIsBattleEnd(bool isBattleEnd);
	
	void printMap() { battleMap_.printMap(); }

	void setHumanUnit(const Pokemon& unit) { humanPlayer_.selectUnit(unit); }
	void setComputerUnit(const Pokemon& unit) { computerPlayer_.selectUnit(unit); }
};

