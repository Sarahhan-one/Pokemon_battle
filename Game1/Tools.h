#pragma once

// STL and useful mathematical tools

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>  // system ÇÔ¼ö
#include "conio.h"

using namespace std;

struct Position {
	int x, y;

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
};

enum class Action {
	STAY, ATTACK, SKILL1, SKILL2, SKILL3, SKILL4
};