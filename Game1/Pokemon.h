#pragma once
#include "Tools.h"
#include "Card.h"

namespace PokemonNamespace {
    enum class Type {
        NORMAL, FIRE, WATER, GRASS, ELECTRIC, ICE, FIGHTING, POISON, GROUND,
        FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY
    };
}

class Pokemon
{
protected:
    vector<PokemonNamespace::Type> types_;
    vector<Card> cards_;
    int maxHp_;
    int hp_;
    Position pos_;
    string name_;
    bool shield_;

public:
    //Pokemon();
    Pokemon(int maxHp, int hp, Position pos);

    vector<PokemonNamespace::Type> getType() const { return types_; }
    int getHp() const { return hp_; }
    int getMaxHp() const { return maxHp_; }
    void setHp(int hp) { hp_ = hp; }
    Position getPos() const { return pos_; }
    void setPos(const Position pos) { pos_ = pos; }
    vector<Card> getCards() const { return cards_; }
    virtual string getName() const { return name_; }
    bool getShield() { return shield_; }
    void setShield(bool shield) { shield_ = shield; }

    bool isAlive() const;
    virtual void takeDamage(const int damage);
    virtual void takeHeal(const int healAmount);
    vector<Position> excuteCard(vector<vector<Pokemon*>>& map, int cardInd);
    vector<Position> rangeMap(vector<vector<Pokemon*>>& map, vector<int>& range);

    //movements
    vector<Position> moveUp(vector<vector<Pokemon*>>& map);
    vector<Position> moveDown(vector<vector<Pokemon*>>& map);
    vector<Position> moveLeft(vector<vector<Pokemon*>>& map);
    vector<Position> moveRight(vector<vector<Pokemon*>>& map);
};



