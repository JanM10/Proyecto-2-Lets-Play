#include "Matriz.h"
int k = 0;
void Matriz::setObsPos()
{
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 21; y++)
		{
			if (cuadradosCancha[x][y].getFillColor() == sf::Color::Blue)
			{
				posicionesX[k] = cuadradosCancha[x][y].getPosition().x;
				posicionesY[k] = cuadradosCancha[x][y].getPosition().y;
				k++;
			}
		}
	}
	k = 0;
}

void Matriz::setResize()
{
	cuadradosCancha.resize(60, vector<sf::RectangleShape>());
}

int Matriz::getPositionX(int posicion)
{
	return posicionesX[posicion];
}

int Matriz::getPositionY(int posicion)
{
	return posicionesY[posicion];
}


