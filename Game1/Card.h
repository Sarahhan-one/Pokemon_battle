#pragma once
#include "Tools.h"
#include <functional>

class Card
{
private:
	string name_;
	std::function<void(vector<vector<Pokemon*>>& map)> executeFunc_;

public:
	Card(string name, std::function<void(vector<vector<Pokemon*>>& map)> executeFunc)
		: name_(name), executeFunc_(executeFunc) {
	}

	string getName() const { return name_; }
	void executeCard(vector<vector<Pokemon*>>& map);
};

