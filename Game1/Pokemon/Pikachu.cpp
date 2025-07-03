#include "Pikachu.h"

vector<Position> Pikachu::thunderbolt(vector<vector<Pokemon*>>& map)
{
    int damage = 50;
    vector<int> range = { 2, 4, 5, 6, 8 };
    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        // Skip self position
        if (attackPos.x == pos_.x && attackPos.y == pos_.y)
            continue;

        // Bounds check (defensive, in case rangeMap ever returns out-of-bounds)
        if (attackPos.y < 0 || attackPos.y >= map.size() ||
            attackPos.x < 0 || attackPos.x >= map[0].size())
            continue;

        Pokemon* target = map[attackPos.y][attackPos.x];
        // Only hit if there is a target and it's not self
        if (target != nullptr && target != this) {
            target->takeDamage(damage);
        }
    }
    return rangeAttack;
}