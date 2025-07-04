#pragma once
#include "HumanPlayer.h"
#include "ComputerPlayer.h"


extern void CallDrawWpfMapFromNative(
	const std::vector<std::vector<std::string>>& paths,
	int playerCurrentHp, int playerMaxHp,
	int computerCurrentHp, int computerMaxHp, string sound_path);
extern void CallShowAvailableCardsFromNative(const std::vector<std::string>& availableCardNames);

enum class BattleResult { NONE, PLAYER_WIN, COMPUTER_WIN };

enum class ImageName {
	BLANK, PIKA, PAI, KKO, NAO, MAJ, TTO
};

class BattleManager
{
private:
	// ~_ 구조가 google, tensorflow 등의 modern c++ style 이라고 해서 사용해봤습니다.
	Player* humanPlayer_;
	Player* computerPlayer_;
	vector<vector<Pokemon*>> map_;
	vector<int> humanCardList_;
	vector<int> computerCardList;
	int currentTurn_;
	bool isBattleEnd_;
	BattleResult lastResult_ = BattleResult::NONE;
	unordered_map<ImageName, string> imageHash_;

public:
	BattleManager() : currentTurn_(0), isBattleEnd_(false),
		humanPlayer_(new HumanPlayer()), computerPlayer_(new ComputerPlayer()),
		map_(vector<vector<Pokemon*>>(MAX_Y, vector<Pokemon*>(MAX_X))) {
	};
	~BattleManager() { delete humanPlayer_;  delete computerPlayer_; }

	void init();
	void executeBattle();
	void selectCardsForStage();
	bool getIsBattleEnd();
	void setIsBattleEnd(bool isBattleEnd);
	Player* getHumanPlayer() { return humanPlayer_; }

	// move, attack 등의 effect 를 print
	void showEffect(vector<Position> poss, CardType cardType, string effectName, string userName);
	void showWpfEffect();

	void printMap();
	void printMap(vector<vector<char>> effectMap);

	void drawWpfMap(); 
	void drawWpfMap(vector<vector<char>> effectMap, CardType cardType, string userName);
	void setHumanPokemon(Pokemon* const pokemon) { humanPlayer_->selectPokemon(pokemon); }
	void setComputerPokemon(Pokemon* const pokemon) { computerPlayer_->selectPokemon(pokemon); }
	BattleResult getLastResult() const { return lastResult_; }
};

