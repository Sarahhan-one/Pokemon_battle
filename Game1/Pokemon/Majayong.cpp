#include "Majayong.h"


vector<Position> Majayong::heal(vector<vector<Pokemon*>> map)
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


vector<Position> Majayong::shield(vector<vector<Pokemon*>> map)
{
    Pokemon* me = this;
    vector<int> range = { 5 };

    vector<Position> shieldRange = rangeMap(map, range);
    me->setShield(true);
    return shieldRange;
}