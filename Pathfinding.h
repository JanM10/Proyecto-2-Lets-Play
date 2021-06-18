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
	typedef pair<int, int> Pair;
	typedef tuple<double, int, int> Tuple;

	//Una estructura para contener los parámetros necesarios
	struct cell {

		Pair parent;
		//Formula: f = g + h
		double f, g, h;
		cell(): parent(-1, -1), f(-1), g(-1), h(-1)
		{
		}
	};

	bool valido(int matriz[11][21], const Pair& point);

	bool desbloqueado(int matriz[11][21], const Pair& point);

	double calcularValorH(const Pair& src, const Pair& dest);

	bool destino(const Pair& position, const Pair& dest);

	void aStarSearch(int matriz[11][21], const Pair& src, const Pair& dest);

	void trazarCamino(const array<array<cell, 21>, 11>& cellDetails, const Pair& dest, int matriz[11][21]);
};

