#include "Kkobugi.h"

vector<Position> Kkobugi::waveCrash(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 4, 5, 6 };

    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        if (attackPos.x == pos_.x && attackPos.y == pos_.y) { // at current position
            continue;
        }
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

vector<Position> Kkobugi::hydroPump(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 1, 2, 3, 5, 7, 8, 9 };

    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        if (attackPos.x == pos_.x && attackPos.y == pos_.y) { // at current position
            continue;
        }
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


vector<Position> Kkobugi::waterGun(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 1, 3, 4, 6, 7, 9 };

    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        if (attackPos.x == pos_.x && attackPos.y == pos_.y) { // at current position
            continue;
        }
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


vector<Position> Kkobugi::tailWhip(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 2, 5, 8 };

    vector<Position> rangeAttack = rangeMap(map, range);

    for (auto& attackPos : rangeAttack) {
        if (attackPos.x == pos_.x && attackPos.y == pos_.y) { // at current position
            continue;
        }
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

