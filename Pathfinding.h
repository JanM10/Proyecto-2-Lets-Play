#pragma once
#include<iostream>
#include <stack>
#include <vector>
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <string>

using namespace std;

class Pathfinding
{
public:
	// Creating a shortcut for int, int pair type
	typedef pair<int, int> Pair;
	// Creating a shortcut for tuple<int, int, int> type
	typedef tuple<double, int, int> Tuple;

	// A structure to hold the neccesary parameters
	struct cell {

		Pair parent;
		// f = g + h
		double f, g, h;
		cell()
			: parent(-1, -1)
			, f(-1)
			, g(-1)
			, h(-1)
		{
		}
	};

	bool isValid(int matriz[11][21], const Pair& point);

	bool isUnBlocked(int matriz[11][21], const Pair& point);

	bool isDestination(const Pair& position, const Pair& dest);

	double calculateHValue(const Pair& src, const Pair& dest);

	void tracePath(const array<array<cell, 21>, 11>& cellDetails, const Pair& dest, int matriz[11][21]);

	void aStarSearch(int matriz[11][21], const Pair& src, const Pair& dest);
};

