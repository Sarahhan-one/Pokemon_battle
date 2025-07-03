#include "Naong.h"


vector<Position> Naong::slash(vector<vector<Pokemon*>> map)
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


vector<Position> Naong::scratch(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 5, 7, 8, 9 };

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


vector<Position> Naong::playRough(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 2, 4, 5, 6 };

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


vector<Position> Naong::furySwipes(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 1, 3, 4, 5, 6, 7, 9 };

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