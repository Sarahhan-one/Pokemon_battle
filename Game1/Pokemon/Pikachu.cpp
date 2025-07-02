#include "Pikachu.h"

vector<Position> Pikachu::thunderbolt(vector<vector<Pokemon*>>& map)
{
    int damage = 10;
    vector<int> range = { 2, 4, 5, 6, 8 };

    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        Pokemon* target = map[attackPos.y][attackPos.x];
        if (target != nullptr) {
            target->takeDamage(damage);
        }
    }

    return rangeAttack;
}