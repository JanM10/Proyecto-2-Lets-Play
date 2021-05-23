#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Menu.h"

using namespace std;
using namespace sf;



int main()
{
	int numeros_random[20];
	int no_repetido;
	srand(time(NULL));
	int g;
	for (int i = 0; i < 20; i++)
	{
		g = i;
		no_repetido = 1 + rand() % (21 - 1);
		for (int j = 0; j <= g; j++)
		{
			if (no_repetido == numeros_random[j]) {
				g = 0;
				i -= 1; 
			}

			while ((g == i) && (no_repetido != numeros_random[j]) && (j==i))
			{
				numeros_random[i] = no_repetido;
				cout << numeros_random[i] << endl;
			}
		} 
	}

	sf::RenderWindow window(sf::VideoMode(900, 900), "SFML WORK!");
	
	sf::CircleShape balon(100);
	balon.setFillColor(Color::Magenta);

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
						//abrir();
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

		window.draw(balon);

		window.display();
	}

	sf::RenderWindow ventana(sf::VideoMode(1400, 800), "Lets play");
	ventana.setFramerateLimit(60);


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
		}
		ventana.clear();
		ventana.display();
	}
}

