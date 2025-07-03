#include "Naong.h"


vector<Position> Naong::slash(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 4, 5, 6 };

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


vector<Position> Naong::scratch(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 5, 7, 8, 9 };

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


vector<Position> Naong::playRough(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 2, 4, 5, 6 };

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


vector<Position> Naong::furySwipes(vector<vector<Pokemon*>> map)
{
    int damage = 15;
    vector<int> range = { 1, 3, 4, 5, 6, 7, 9 };

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