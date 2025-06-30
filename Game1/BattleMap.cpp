#include "BattleMap.h"

BattleMap::BattleMap(Position pos) : pos_(pos),
    grid_(vector<vector<int>> (pos.y, vector<int>(pos.x)))
{
}

bool BattleMap::isWalkable(Position pos)
{
    if (pos.y < 0 || pos.y >= grid_.size() || pos.x < 0 || pos.x >= grid_[0].size())
        return false;
    return grid_[pos.y][pos.x] == 0; // 0 means empty
}

void BattleMap::printMap()
{
    for (int i = 0; i < grid_[0].size(); i++) {
        for (auto tile : grid_[i]) {
            cout << tile << ' ';
        }
        cout << '\n';
    }
}
