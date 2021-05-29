#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Menu.h"

using namespace std;
using namespace sf;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[20]);
Vector2f v_przesun(-5, 0); //Vector que se va a usar para mover la bola

/// <summary>
/// Esta clase se encarga de crear la pelota para jugar
/// Tambien se encarga de las fisicas detras de la misma
/// </summary>
class Pilka :public CircleShape //Se crea la clase de la pelota
{
public:

    Pilka(float r = 50) :CircleShape(r) //Se deciden los parametros del balon
    {
        this->setOrigin(r, r);
        this->setPosition(700, 200);
        this->setFillColor(Color(56, 200, 210));
    }

    void przesun()
    {
        if (this->getPosition().x <= 50 || this->getPosition().x >= 1400) //Se deciden los bordes de la ventana donde debe rebotar
        {
            v_przesun.x *= -1;
        }
        if (this->getPosition().y <= 50 || this->getPosition().y >= 800)
        {
            v_przesun.y *= -1;
        }
        this->move(v_przesun);
        
    }



};
class Bola :public CircleShape
{
public:

    Bola(float r = 50) :CircleShape(r)
    {
        this->setOrigin(r, r);
        this->setPosition(350, 200);
        this->setFillColor(Color(255, 0, 0));
    }


};

int main()
{
	srand(time(NULL)); //Numeros aleatorios
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
    int klatki = 0;
    Pilka pilka; //Se crea la pelota
    Bola bola;

    Event e;

    while (ventana.isOpen())
    {
        while (ventana.pollEvent(e))
        {
            if (e.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape))) //Cerrar la ventana con la tecla Escape
                ventana.close();

            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) //Aqui se decide como la pelota se mueve segun la posicion del mouse
            {
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x - 50 &&  //Esquina superior izquierda
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x - 18 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y - 50 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y - 18)
                {
                    v_przesun.x = 5;
                    v_przesun.y = 5;
                }

                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x - 33 &&  //Arriba
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x + 33 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y - 50 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y - 18)
                {
                    v_przesun.x = 0;
                    v_przesun.y = 5;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x + 34 &&  //Esquina superior derecha
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x + 50 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y - 50 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y - 17)
                {
                    v_przesun.x = -5;
                    v_przesun.y = 5;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x - 50 &&  //Izquierda
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x - 18 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y - 18 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y + 17)
                {
                    v_przesun.x = 5;
                    v_przesun.y = 0;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x + 18 &&  //Derecha
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x + 50 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y - 17 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y + 18)
                {
                    v_przesun.x = -5;
                    v_przesun.y = 0;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x - 17 &&  //Abajo
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x + 17 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y + 18 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = 0;
                    v_przesun.y = -5;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x - 50 &&  //Esquina inferior izquierda
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x - 18 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y + 18 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = 5;
                    v_przesun.y = -5;
                }
                if (Mouse::getPosition(ventana).x >= pilka.getPosition().x + 18 &&  //Esquina inferior derecha
                    Mouse::getPosition(ventana).x <= pilka.getPosition().x + 100 &&
                    Mouse::getPosition(ventana).y >= pilka.getPosition().y + 18 &&
                    Mouse::getPosition(ventana).y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = -5;
                    v_przesun.y = -5;
                }
                          
            }

            if (bola.getGlobalBounds().intersects(pilka.getGlobalBounds())) //Aqui se experimenta con el rebote con obstaculos
            {
                if (bola.getPosition().x >= pilka.getPosition().x - 50 &&  //Esquina superior izquierda
                    bola.getPosition().x <= pilka.getPosition().x - 18 &&
                    bola.getPosition().y >= pilka.getPosition().y - 50 &&
                    bola.getPosition().y <= pilka.getPosition().y - 18)
                {
                    v_przesun.x = 5;
                    v_przesun.y = 5;
                }

                if (bola.getPosition().x >= pilka.getPosition().x - 33 &&  //Arriba
                    bola.getPosition().x <= pilka.getPosition().x + 33 &&
                    bola.getPosition().y >= pilka.getPosition().y - 50 &&
                    bola.getPosition().y <= pilka.getPosition().y - 18)
                {
                    v_przesun.x = 0;
                    v_przesun.y = 5;
                }
                if (bola.getPosition().x >= pilka.getPosition().x + 34 &&  //Esquina superior derecha
                    bola.getPosition().x <= pilka.getPosition().x + 50 &&
                    bola.getPosition().y >= pilka.getPosition().y - 50 &&
                    bola.getPosition().y <= pilka.getPosition().y - 17)
                {
                    v_przesun.x = -5;
                    v_przesun.y = 5;
                }
                if (bola.getPosition().x >= pilka.getPosition().x - 50 &&  //Izquierda
                    bola.getPosition().x <= pilka.getPosition().x - 18 &&
                    bola.getPosition().y >= pilka.getPosition().y - 18 &&
                    bola.getPosition().y <= pilka.getPosition().y + 17)
                {
                    v_przesun.x = 5;
                    v_przesun.y = 0;
                }
                if (bola.getPosition().x >= pilka.getPosition().x + 18 &&  //Derecha
                    bola.getPosition().x <= pilka.getPosition().x + 50 &&
                    bola.getPosition().y >= pilka.getPosition().y - 17 &&
                    bola.getPosition().y <= pilka.getPosition().y + 18)
                {
                    v_przesun.x = -5;
                    v_przesun.y = 0;
                }
                if (bola.getPosition().x >= pilka.getPosition().x - 17 &&  //Abajo
                    bola.getPosition().x <= pilka.getPosition().x + 17 &&
                    bola.getPosition().y >= pilka.getPosition().y + 18 &&
                    bola.getPosition().y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = 0;
                    v_przesun.y = -5;
                }
                if (bola.getPosition().x >= pilka.getPosition().x - 50 &&  //Esquina inferior izquierda
                    bola.getPosition().x <= pilka.getPosition().x - 18 &&
                    bola.getPosition().y >= pilka.getPosition().y + 18 &&
                    bola.getPosition().y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = 5;
                    v_przesun.y = -5;
                }
                if (bola.getPosition().x >= pilka.getPosition().x + 18 &&  //Esquina inferior derecha
                    bola.getPosition().x <= pilka.getPosition().x + 100 &&
                    bola.getPosition().y >= pilka.getPosition().y + 18 &&
                    bola.getPosition().y <= pilka.getPosition().y + 50)
                {
                    v_przesun.x = -5;
                    v_przesun.y = -5;
                }
            }
            
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right) //Detener la pelota
            {
                v_przesun.x = 0;
                v_przesun.y = 0;
            }
        }

        ventana.clear(Color::White);

        klatki += 1;
        if (klatki == 60)
        {
            cout << "*";
            klatki = 0;
        }

        pilka.przesun();
        ventana.draw(pilka);
        ventana.draw(bola);
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

