#include "Pokemon.h"

//Pokemon::Pokemon() : Pokemon(0, 0, Position())
//{
//}

Pokemon::Pokemon(int maxHp, int hp, Position pos)
	: maxHp_(maxHp), hp_(hp), pos_(pos)
{
	static vector<Position> res;
	cards_.push_back(Card("MoveUp", CardType::MOVE, [this](vector<vector<Pokemon*>>& map) -> vector<Position> {
		return moveUp(map);
		}));
	cards_.push_back(Card("MoveDown", CardType::MOVE, [this](vector<vector<Pokemon*>>& map) -> vector<Position> {
		return moveDown(map);
		}));
	cards_.push_back(Card("MoveLeft", CardType::MOVE, [this](vector<vector<Pokemon*>>& map) -> vector<Position> {
		return moveLeft(map);
		}));
	cards_.push_back(Card("MoveRight", CardType::MOVE, [this](vector<vector<Pokemon*>>& map) -> vector<Position> {
		return moveRight(map);
		}));
}

bool Pokemon::isAlive() const
{
	return hp_ > 0;
}

void Pokemon::takeDamage(int damage)
{
	hp_ -= damage;
}

void Pokemon::takeHeal(int healAmount)
{
	hp_ += healAmount;
}

vector<Position> Pokemon::excuteCard(vector<vector<Pokemon*>>& map, int cardInd)
{
	return cards_[cardInd].executeCard(map);
}

vector<Position> Pokemon::rangeMap(vector<vector<Pokemon*>>& map, vector<int>& range) {
	vector<Position> tmp = {};
	for (auto& point : range) {
		if (point == 1)	tmp.push_back({ pos_.y - 1, pos_.x - 1 });
		if (point == 2) tmp.push_back({ pos_.y - 1, pos_.x });
		if (point == 3) tmp.push_back({ pos_.y - 1, pos_.x + 1 });
		if (point == 4) tmp.push_back({ pos_.y, pos_.x - 1 });
		if (point == 5) tmp.push_back({ pos_.y, pos_.x }); 
		if (point == 6) tmp.push_back({ pos_.y, pos_.x + 1 });
		if (point == 7) tmp.push_back({ pos_.y + 1, pos_.x - 1 });
		if (point == 8) tmp.push_back({ pos_.y + 1, pos_.x });
		if (point == 9)	tmp.push_back({ pos_.y + 1, pos_.x + 1 });
	}
	return tmp;
}

vector<Position> Pokemon::moveUp(vector<vector<Pokemon*>>& map)
{
	vector<Position> result;
	if (pos_.y > 0 && map[pos_.y - 1][pos_.x] == nullptr) {
		map[pos_.y][pos_.x] = nullptr;
		pos_.y -= 1;
		map[pos_.y][pos_.x] = this;
	}
	return result;
}

vector<Position> Pokemon::moveDown(vector<vector<Pokemon*>>& map)
{
	vector<Position> result;
	if (pos_.y + 1 < MAX_Y && map[pos_.y + 1][pos_.x] == nullptr) {
		map[pos_.y][pos_.x] = nullptr;
		pos_.y += 1;
		map[pos_.y][pos_.x] = this;
	}
	return result;
}

vector<Position> Pokemon::moveLeft(vector<vector<Pokemon*>>& map)
{
	vector<Position> result;
	if (pos_.x > 0 && map[pos_.y][pos_.x - 1] == nullptr) {
		map[pos_.y][pos_.x] = nullptr;
		pos_.x -= 1;
		map[pos_.y][pos_.x] = this;
	}
	return result;
}

vector<Position> Pokemon::moveRight(vector<vector<Pokemon*>>& map)
{
	vector<Position> result;
	if (pos_.x + 1 < MAX_X && map[pos_.y][pos_.x + 1] == nullptr) {
		map[pos_.y][pos_.x] = nullptr;
		pos_.x += 1;
		map[pos_.y][pos_.x] = this;
	}
	return result;
}
