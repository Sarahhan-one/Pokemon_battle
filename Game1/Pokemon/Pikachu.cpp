#include "Pikachu.h"

vector<Position> Pikachu::thunderbolt(vector<vector<Pokemon*>> map)
{
    int damage = 20;
    vector<int> range = { 2,5, 8 };

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

vector<Position> Pikachu::disCharge(vector<vector<Pokemon*>> map)
{
    int damage = 20;
    vector<int> range = { 7, 5, 8, 9 };

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

vector<Position> Pikachu::electricBall(vector<vector<Pokemon*>> map)
{
    int damage = 10;
    vector<int> range = { 1, 2, 3, 5 };

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

vector<Position> Pikachu::spark(vector<vector<Pokemon*>> map)
{
    int damage = 20;
    vector<int> range = { 1, 3, 5, 7, 9 };

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

vector<Position> Pikachu::heal(vector<vector<Pokemon*>> map)
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


vector<Position> Pikachu::shield(vector<vector<Pokemon*>> map)
{
    Pokemon* me = this;
    vector<int> range = { 5 };

    vector<Position> shieldRange = rangeMap(map, range);
    me->setShield( true );
    return shieldRange;
}

