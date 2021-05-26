#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Menu.h"

using namespace std;
using namespace sf;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[20]);

int main()
{
	srand(time(NULL)); //Numeros aleatorios
	int arreglo[20], num = 0;

	//Para que no se repitan los numeros en el arreglo

	for (int i = 0; i < 20; i++)
	{
		while (verificar(num, arreglo)) {

			num = rand() % (21 - 1); 
		}

		arreglo[i] = num;
	}

	for (int i = 0; i < 20; i++)
	{
		cout << arreglo[i] << " ";
	}

	RenderWindow window(sf::VideoMode(900, 900), "Let's Play!");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Genetic Puzzle se esta abriendo" << std::endl;
						//window.setVisible(false);
						window.close();
						break;
					case 1:
						std::cout << "BP Game se esta abriendo" << std::endl;
						break;
					case 2:
						std::cout << "Abriendo las opciones" << std::endl;
						break;
					case 3:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		menu.draw(window);

		window.display();
	}

	sf::RenderWindow ventana(sf::VideoMode(1400, 800), "BP GAME");
	ventana.setFramerateLimit(120);

	sf::Vector2i player = sf::Vector2i(13, 13);
	sf::RectangleShape playerRect = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
	playerRect.setPosition(player.x * 40.f, player.x * 40.f);
	playerRect.setFillColor(sf::Color(0, 180, 0));
	playerRect.setOutlineThickness(1.f);
	playerRect.setOutlineColor(sf::Color(0 ,0, 0));

	sf::Vector2i opponent = sf::Vector2i(1, 1);
	sf::RectangleShape opponentRect = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
	opponentRect.setPosition(opponent.x * 40.f, opponent.x * 40.f);
	opponentRect.setFillColor(sf::Color(190, 0, 0));
	opponentRect.setOutlineThickness(1.f);
	opponentRect.setOutlineColor(sf::Color(0, 0, 0));

	int gameMap[15 * 15];
	sf::RectangleShape displayRects[15 * 15];

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			displayRects[i + j * 15].setPosition(i * 40.f, j * 40.f);
			displayRects[i + j * 15].setSize(sf::Vector2f(40.f, 40.f));
			displayRects[i + j * 15].setOutlineThickness(1.f);
			displayRects[i + j * 15].setOutlineColor(sf::Color(0, 0, 0));

			if (!(i == opponent.x && j == opponent.y) && !(i == player.x && j == player.y))
			{
				//Se colorean cuadrados aleatoriamente 
				if (rand() / (float)RAND_MAX < 0.22f || i == 0 || j == 0 || i == 14 || j == 14)
				{
					gameMap[i + j * 15] = 1;
					displayRects[i + j * 15].setFillColor(sf::Color(0, 0, 0));
				}
			}
		}
	}

	//CircleShape balon(100);
	//balon.setFillColor(Color::Magenta);

	while (ventana.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop

		sf::Event event;
		while (ventana.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				ventana.close();
				break;

			case Event::MouseButtonReleased:
				cout << "Se preciono" << endl;

				switch (event.key.code)
				{
				case Mouse::Left:
					cout << "Se preciono la izquierda" << endl;
					break;
				}
				break;
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				ventana.close();
			}	
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (gameMap[player.x + (player.y - 1) * 15] != 1) player.y -= 1;
					break;
				case sf::Keyboard::Down:
					if (gameMap[player.x + (player.y + 1) * 15] != 1) player.y += 1;
					break;
				case sf::Keyboard::Right:
					if (gameMap[player.x + (player.y + 1) * 15] != 1) player.x += 1;
					break;
				case sf::Keyboard::Left:
					if (gameMap[player.x + (player.y - 1) * 15] != 1) player.x -= 1;
					break;
				default:
					break;
				}
			}

			playerRect.setPosition(player.x * 40.f, player.y * 40.f);
		}
		//Updates the game 
		ventana.clear(sf::Color(255, 255, 255));

		//ventana.draw(balon);

		for (int i = 0; i < 15 * 15; i++)
		{
			ventana.draw(displayRects[i]);
		}

		ventana.draw(playerRect);
		ventana.draw(opponentRect);

		ventana.display();
	}
	
}

//Esta funcion se encarga de verificar que no se repita ningun numero en el arreglo
bool verificar(int num, int arreglo[20]) 
{
	for (int i = 0; i < 20; i++)
	{
		if (num == arreglo[i]) {
			return true; //Si el numero ya existe retorna verdadero.
		}
	}
	return false; //Si el numero NO existe retorna falso.
}

