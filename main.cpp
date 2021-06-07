#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <string>
#include "windows.h"

#include "Menu.h"
#include "Backtracking.h"
#include "Pathfinding.h"
#include "Textbox.h"
#include "World.h"
#include "WorldRenderer.h"
#include "Ball.h"

//Instancias de las clases Backtracking y Pathfinding
Backtracking BT;
Pathfinding PF;

using namespace std;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[9]);

void numerosRandom(int matriz[11][21]);

void imprimitMatriz(int matriz[11][21]);

void limpiarMatriz(int resultado[11][21]);

void matrizRespaldo(int matriz[11][21]);

void asignarColores(int matriz[11][21]);

void mostrarBT(int resultado[11][21], int matriz[11][21]);

bool flag = true;//Para ver cual ventana se abre si el BP game o el Puzzle

int cantObs;//Cantidad de obstaculos

int compuGoles = 0, jugadorGoles = 0;

int resultado[11][21]{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int colores[11][21]{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for tuple<int, int, int> type
typedef tuple<double, int, int> Tuple;


int main()
{
	srand((unsigned)(time(NULL)));

	RenderWindow window(sf::VideoMode(900, 900), "Let's Play!");
	Menu menu(window.getSize().x, window.getSize().y);

	//Este ciclo abre el menu principal
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
						window.close();
						break;
					case 1:
						std::cout << "BP Game se esta abriendo" << std::endl;
						flag = false;
						window.close();
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

	//Si el flag es falso se abre la ventana del BP Game
	if (flag == false)
	{
		sf::RenderWindow obstaculos(sf::VideoMode(400, 200), "Cuantos Obstaculos");

		sf::Font arial;
		arial.loadFromFile("arial.ttf");
		Textbox textbox(15, sf::Color::White, true);
		
		textbox.setFont(arial);
		textbox.setPosition({ 100, 100 });
		textbox.setLimit(true, 1);


		Textbox textbox2(15, sf::Color::White, false);

		textbox2.setString("Escriba la cantidadn de jugadores que desea:");
		textbox2.setFont(arial);
		textbox2.setPosition({ 75, 50 });
		

		///////////////////////////////////////////////////////////////////////
		//El programa sigue corriendo siempre y cuando la ventana este abierta
		while (obstaculos.isOpen())
		{

			//Revisa todos los eventos que se activaron desde la ultima iteracion 
			sf::Event event;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				cantObs = textbox.getText().front() - 48;
				obstaculos.close();
			}
			while (obstaculos.pollEvent(event)){

				//Se cierra la ventana
				switch (event.type)
				{
				case sf::Event::Closed:					
					obstaculos.close();

				case::Event::TextEntered:
					textbox.typedOn(event);
				}
				
		
			}
			
			obstaculos.clear();
			textbox2.drawTo(obstaculos);
			textbox.drawTo(obstaculos);
			obstaculos.display();
		}
		/////////////////////////////////////////////////////////////////////

		sf::RenderWindow ventanaPrueba(sf::VideoMode(1400, 800), "BP Game");

		sf::Text marcador, textoCompu, textoJugador, ganador;
		marcador.setFont(arial);
		textoCompu.setFont(arial);
		textoJugador.setFont(arial);
		ganador.setFont(arial);
		ganador.setCharacterSize(50);

		marcador.setString("Cantida maxima de anotaciones: 5");
		marcador.setPosition(sf::Vector2f(500, 25));

		textoCompu.setString("Computadora: " + to_string(compuGoles));
		textoCompu.setPosition(sf::Vector2f(250, 725));

		textoJugador.setString("Jugador: " + to_string(jugadorGoles));
		textoJugador.setPosition(sf::Vector2f(900, 725));


		const int chanchaDim = 60; //Dimensiones de la cancha
		sf::RectangleShape cuadrados(sf::Vector2f(chanchaDim, chanchaDim));
		ventanaPrueba.setFramerateLimit(60);

		const int tamanoCancha = 22;//Cantidad maxima de cuadrados que puede haber por fila y columna

		vector<vector<RectangleShape>> cuadradosCancha;//En ese vector se almacenan los cuadrados de la cancha

		cuadradosCancha.resize(tamanoCancha, vector<sf::RectangleShape>());

		World world;
		WorldRenderer worldRenderer(world);

		sf::Vertex line[] = { sf::Vertex(sf::Vector2f(-1, -1)), sf::Vertex(sf::Vector2f(-1, -1)) };

		bool dragging = false;

		float deltatime = 0.f;
		sf::Clock clock;

		//Este for rellena la el vector con los cuadrados que se van a mostrar en pantalla, junto con sus colores y rayas
		for (int x = 0; x < 11; x++)
		{
			cuadradosCancha[x].resize(tamanoCancha, sf::RectangleShape());
			for (int y = 0; y < 21; y++)
			{
				cuadradosCancha[x][y].setSize(sf::Vector2f(chanchaDim, chanchaDim));
				cuadradosCancha[x][y].setFillColor(Color::Green);
				cuadradosCancha[x][y].setOutlineThickness(3.0f);
				cuadradosCancha[x][y].setOutlineColor(Color::Black);
				cuadradosCancha[x][y].setPosition((y + 1) * chanchaDim, (x + 1) * chanchaDim);
			}
		}

		//Matriz de la cancha, cada numero representa algo a la hora de imprimirse
		int cuadrosCancha2[11][21]{ 
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 } };

		numerosRandom(cuadrosCancha2);

		matrizRespaldo(cuadrosCancha2);


		// run the program as long as the window is open
		while (ventanaPrueba.isOpen())
		{
			deltatime = clock.restart().asSeconds();

			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (ventanaPrueba.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					ventanaPrueba.close();
				
				switch (event.type) {

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2i point = sf::Mouse::getPosition(ventanaPrueba);

						if (world.dragBall(sf::Vector2f((float)point.x, (float)point.y))) {
							dragging = true;
						}

					}
					break;

				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) {

						world.setDraggedVelocity(line[1].position.x, line[1].position.y);
						dragging = false;
					}
					break;
				}

				
			}
			ventanaPrueba.clear(sf::Color::Black);

			int posX = (worldRenderer.getPositionX(ventanaPrueba) / 60) - 1;
			int posY = (worldRenderer.getPositionY(ventanaPrueba) / 60) - 1;

			if (worldRenderer.getVelocityX(ventanaPrueba) <= 0.01 && worldRenderer.getVelocityY(ventanaPrueba) <= 0.01
				|| worldRenderer.getVelocityX(ventanaPrueba) == 0 && worldRenderer.getVelocityY(ventanaPrueba) == 0)
			{
				worldRenderer.getPositionX(ventanaPrueba);
				worldRenderer.getPositionY(ventanaPrueba);

				cout << "X: " << posX << " " << "Y: " << posY << endl;

				////Src(source) es el inicio del pathfinding
				Pair src(posY, posX);
				//Pair src(5, 10);
				////Dest muestra el destino del pathfinding
				Pair dest(5, 19);

				PF.aStarSearch(cuadrosCancha2, src, dest);

			}
			else
			{
				asignarColores(cuadrosCancha2);
			}

			//BT.hallarCamino(cuadrosCancha2, 5, 10, 5, 1, resultado);

			//mostrarBT(resultado, cuadrosCancha2);

			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 21; y++)
				{
					if (cuadrosCancha2[x][y] == 1)
					{
						cuadradosCancha[x][y].setFillColor(Color::Blue);//El azul muestra los obstaculos del mapa 
					}
					else if (cuadrosCancha2[x][y] == 2) {
						cuadradosCancha[x][y].setFillColor(Color::Red);//El rojo muestra las porterias
					}
					else if (cuadrosCancha2[x][y] == 3) {
						cuadradosCancha[x][y].setFillColor(Color::Black);//El negro muestra los bordes del mapa
					}
					else if (cuadrosCancha2[x][y] == 4) {//El color blanco representa la ruta del pathfinding
						cuadradosCancha[x][y].setFillColor(Color::White);
					}

				}

			}
			
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 21; y++)
				{
					ventanaPrueba.draw(cuadradosCancha[x][y]);
				}
			}
			if (dragging) {
				sf::Vector2i point = sf::Mouse::getPosition(ventanaPrueba);

				line[0] = sf::Vertex(sf::Vector2f(world.getDraggedBall()->getPosition()), sf::Color::Blue);
				line[1] = sf::Vertex(sf::Vector2f((float)point.x, (float)point.y), sf::Color::Blue);
				
			}
			if (dragging) {
				ventanaPrueba.draw(line, 2, sf::Lines);
			}

			if (compuGoles == 5)
			{
				ventanaPrueba.clear(sf::Color::Black);
				ganador.setString("El ganador es la Computadora");
				ganador.setPosition(sf::Vector2f(350, 500));
				ventanaPrueba.draw(ganador);

			}
			else if (jugadorGoles == 5)
			{
				ventanaPrueba.clear(sf::Color::Black);
				ganador.setString("Felicidades eres el ganador!");
				ganador.setPosition(sf::Vector2f(400, 500));
				ventanaPrueba.draw(ganador);
			}

			int CL = worldRenderer.getLado(ventanaPrueba);

			if (CL == 1)
			{
				compuGoles += 1;
				worldRenderer.setLado(ventanaPrueba);
				textoCompu.setString("Computadora: " + to_string(compuGoles));
			}
			else if (CL == 2)
			{
				jugadorGoles += 1;
				worldRenderer.setLado(ventanaPrueba);
				textoJugador.setString("Jugador: " + to_string(jugadorGoles));
			}



			worldRenderer.render(ventanaPrueba);
			ventanaPrueba.draw(marcador);
			ventanaPrueba.draw(textoCompu);
			ventanaPrueba.draw(textoJugador);
			ventanaPrueba.display();
			world.update(deltatime);
		}

	}else 
{
	/*
	* 
	* 
	*/
	}
}


//Esta funciona elige las posiciones de los judagores o obstaculos aleatoriamente
void numerosRandom(int matriz[11][21]) {
	srand(time(NULL)); //Numeros aleatorios


	int filas[9], columnas[9], num = 1 + rand() % (9);

	for (int i = 9; i > abs(cantObs-9); i--)
	{
		filas[i-1] = 0;
		columnas[i-1] = 0;
	}

	//Para que no se repitan los numeros de filas
	for (int i = 0; i < cantObs; i++)
	{
		while (verificar(num, filas) && num != 0) {

			num = 1 + rand() % (9);
			
		}
		filas[i] = num;
	}

	//Para que no se repitan los numeros de columnas
	for (int i = 0; i < cantObs; i++)
	{
		while (verificar(num, columnas) && num != 0) {

			num = 1 + rand() % (9);
		}
		columnas[i] = num;
	}

	// 20-#columna para poder hacer la reflexion del otro lado de la matriz
	for (int x = 0; x < cantObs; x++)
	{
		matriz[filas[x]][columnas[x]] = 1;
		matriz[filas[x]][20-columnas[x]] = 1;
	}

	imprimitMatriz(matriz);

}

//Imprime los valores numericos de la matriz en consola
void imprimitMatriz(int matriz[11][21])
{
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 21; y++)
		{
			cout << matriz[x][y] << " ";
		}
		cout << endl;
	}
}


//Esta funcion se encarga de verificar que no se repita ningun numero en el arreglo
bool verificar(int num, int arreglo[9])
{
	for (int i = 0; i < 9; i++)
	{
		if (num == arreglo[i]) {
			return true; //Si el numero ya existe retorna verdadero.
		}
	}
	return false; //Si el numero NO existe retorna falso.
}

//Limpia la ruta del resultado para que se pueda volver a usar
void limpiarMatriz(int resultado[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			resultado[i][j] = 1;
		}
	}
	imprimitMatriz(resultado);
}

void matrizRespaldo(int matriz[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			colores[i][j] = matriz[i][j];
		}
	}
	//imprimitMatriz(colores);
}

void asignarColores(int matriz[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			matriz[i][j] = colores[i][j];
		}
	}
	//imprimitMatriz(colores);
}

void mostrarBT(int resultado[11][21], int matriz[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (resultado[i][j] == 0)
			{
				matriz[i][j] = 4;
			}
		}
	}
}


