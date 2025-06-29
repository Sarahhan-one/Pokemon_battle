#pragma once
#include "Tools.h"

class BattleMap
{
private:
	Position pos_;
	// 코테에서 사용하는 vector 를 사용했습니다. 나중에 enum 으로 바꿔도 좋을 듯 합니다.
	vector<vector<int>> grid_;

public:
	BattleMap(): pos_(Position(5,5)), grid_() {}
	BattleMap(Position pos);

	void setTile(Position pos, int value) { grid_[pos.y][pos.x] = value; }
	int getTile(Position pos) { return grid_[pos.y][pos.x]; }
	bool isWalkable(Position pos);
	void printMap();
};

