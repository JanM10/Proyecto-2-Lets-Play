#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Ball.h"
#include "WorldRenderer.h"
#include <vector>
#include "World.h"

#include "Menu.h"

using namespace std;
using namespace sf;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[20]);

/// <summary>
/// Esta clase se encarga de crear la pelota para jugar
/// Tambien se encarga de las fisicas detras de la misma
/// </summary>


int main()
{
	srand((unsigned)(time(NULL))); //Numeros aleatorios
	int arreglo[20], num = 0;

	//Para que no se repitan los numeros en el arreglo

	for (int i = 0; i < 20; i++)
	{
		while (verificar(num, arreglo)) {

			num = rand() % (21 - 1); //
		}

		arreglo[i] = num;
	}

	for (int i = 0; i < 20; i++)
	{
		cout << arreglo[i] << " ";
	}

	RenderWindow window(sf::VideoMode(900, 900), "Let's Play!"); //Aqui esta la ventana del menu principal

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) //Durante el tiempo que la ventana esté abierta se mueve a travez del menu con las teclas
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

    sf::RenderWindow ventana(sf::VideoMode(1400, 800), "BP Game"); //Ventana donde se encuentra BP Game
    ventana.setFramerateLimit(120);

	World world;
	WorldRenderer worldRenderer(world);

	sf::Vertex line [] = { sf::Vertex(sf::Vector2f(-1, -1)), sf::Vertex(sf::Vector2f(-1, -1)) };

	bool dragging = false;

	float deltatime = 0.f;
	sf::Clock clock;

    Event e;

    while (ventana.isOpen())
    {
		deltatime = clock.restart().asSeconds();

		while (ventana.pollEvent(e))
		{
			switch (e.type) {
			case sf::Event::Closed:
				ventana.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i point = sf::Mouse::getPosition(ventana);

					if (world.dragBall(sf::Vector2f((float)point.x, (float)point.y))) {
						dragging = true;
					}

				}
				break;

			case sf::Event::MouseButtonReleased:
				if (e.mouseButton.button == sf::Mouse::Left) {

					world.setDraggedVelocity(line[1].position.x, line[1].position.y);

					dragging = false;
				}
				break;
			}
		}
		if (dragging) {
			sf::Vector2i point = sf::Mouse::getPosition(ventana);

			line[0] = sf::Vertex(sf::Vector2f(world.getDraggedBall()->getPosition()), sf::Color::Blue);
			line[1] = sf::Vertex(sf::Vector2f((float)point.x, (float)point.y), sf::Color::Blue);
		}
        world.update(deltatime);

		ventana.clear(sf::Color::White);
		worldRenderer.render(ventana);

		if (dragging) {
			ventana.draw(line, 2, sf::Lines);
		}
		ventana.display();

	}

	return 0;
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

