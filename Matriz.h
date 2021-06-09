#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_set>

using namespace std;


class Matriz
{
public:
	vector<vector<sf::RectangleShape>> cuadradosCancha;//En ese vector se almacenan los cuadrados de la cancha

	int posicionesX[18];

	int posicionesY[18];

	void setObsPos();

	void setResize();

	int getPositionX(int posicion);

	int getPositionY(int posicion);

};


