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
	int y, x;

	Position() : y(0), x(0) {}
	Position(int y, int x) : y(y), x(x) {}
};
