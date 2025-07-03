#include "Pikachu.h"


vector<Position> Pikachu::thunderbolt(vector<vector<Pokemon*>>& map)
{
    int damage = 50;
    vector<int> range = { 2, 4, 5, 6, 8 };
    vector<Position> rangeAttack = rangeMap(map, range);

    // Find the opponent in the map
    Pokemon* opponent = nullptr;
    for (const auto& row : map) {
        for (Pokemon* p : row) {
            if (p && p != this) {
                opponent = p;
                break;
            }
        }
        if (opponent) break;
    }

    if (opponent) {
        Position oppPos = opponent->getPos();
        for (const auto& attackPos : rangeAttack) {
            if (attackPos.x == oppPos.x && attackPos.y == oppPos.y) {
                opponent->takeDamage(damage);
                break; // Only hit once
            }
        }
    }

    return rangeAttack;
}