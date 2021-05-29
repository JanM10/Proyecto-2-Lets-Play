#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Menu.h"

using namespace std;
using namespace sf;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[20]);
Vector2f v_przesun(-5, 0);
class Pilka :public CircleShape
{
public:

    Pilka(float r = 50) :CircleShape(r)
    {
        this->setOrigin(r, r);
        this->setPosition(700, 200);
        this->setFillColor(Color(56, 200, 210));
    }

    void przesun()
    {
        if (this->getPosition().x <= 50 || this->getPosition().x >= 1400)
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

	/*sf::RenderWindow ventana(sf::VideoMode(1400, 800), "Lets play");
    ventana.setFramerateLimit(120);
    int klatki = 0;
    Pilka pilka;
    Bola bola;*/

    Event e;
    sf::RenderWindow app(VideoMode(256, 356), "FLDSMDFR");
    app.setFramerateLimit(60);
    Texture t;
    t.loadFromFile("images/smiley.png");
    int w = 64;
    int grid[6][6] = { 0 };
    Sprite sprite[20];


    int n = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            n++;
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(IntRect(i * w, j * w, w, w));
            grid[i + 1][j + 1] = n;
        }

    while (app.isOpen())
    {



        
        
      
           

            while (app.isOpen())
            {
                Event e;
                while (app.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        app.close();

                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left)
                        {
                            Vector2i pos = Mouse::getPosition(app);
                            int x = pos.x / w + 1;
                            int y = pos.y / w + 1;

                            int dx = 0;
                            int dy = 0;

                            if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
                            if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
                            if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
                            if (grid[x - 1][y] == 16) { dx = -1; dy = 0; };

                            int n = grid[x][y];
                            grid[x][y] = 16;
                            grid[x + dx][y + dy] = n;

                            /*
                            //animation
                            sprite[16].move(-dx * w, -dy * w);
                            float speed = 3;

                            for (int i = 0; i < w; i += speed)
                            {
                                sprite[n].move(speed * dx, speed * dy);
                                app.draw(sprite[16]);
                                app.draw(sprite[n]);
                                app.display();
                            }
                            */
                        }

                }

                app.clear(Color::Color(82, 82, 82));
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                    {
                        int n = grid[i + 1][j + 1];
                        sprite[n].setPosition(i * w, j * w);
                        app.draw(sprite[n]);
                    }

                app.display();
            }

            return 0;
        }

        app.display();
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

