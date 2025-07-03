#include "Kkobugi.h"

vector<Position> Kkobugi::waveCrash(vector<vector<Pokemon*>> map)
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

vector<Position> Kkobugi::hydroPump(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 1, 2, 3, 5, 7, 8, 9 };

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


vector<Position> Kkobugi::waterGun(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 1, 3, 4, 6, 7, 9 };

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


vector<Position> Kkobugi::tailWhip(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 2, 5, 8 };

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


vector<Position> Kkobugi::heal(vector<vector<Pokemon*>> map)
{
    int healAmount = 20;
    vector<int> range = { 5 };

    vector<Position> healRange = rangeMap(map, range);

    Pokemon* me = this;
    if (me->getHp() + 20 > me->getMaxHp()) {
        me->setHp(me->getMaxHp());
    }
    else {
        me->setHp(me->getHp() + 20);
    }
    return healRange;
}