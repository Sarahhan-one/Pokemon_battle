#include "BattleMap.h"

BattleMap::BattleMap(Position pos) : pos_(pos),
    grid_(vector<vector<int>> (pos.y, vector<int>(pos.x)))
{
}

bool BattleMap::isWalkable(Position pos)
{
    return false;
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
