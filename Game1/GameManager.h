#pragma once
#include "BattleManager.h"

enum class GameState
{
	MENU, BATTLE, EXIT
};

class GameManager
{
private:
	GameState gameState_;
	int stageNumber_;
	BattleManager battleManager_;

public:
	GameManager(): gameState_(GameState::MENU), stageNumber_(0), battleManager_(BattleManager()) {}
	
	void init();
	void menu();
	void startBattle();
	void update();
	void endBattle();
	void selectCharacter();
	Pokemon* createOpponentForStage(int stage);
	void main();
	void exitGame();
};
