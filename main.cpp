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

#include "Menu.h"
#include "Backtracking.h"
#include "Pathfinding.h"

//Instancias de las clases Backtracking y Pathfinding
Backtracking BT;
Pathfinding PF;

using namespace std;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[9]);

void numerosRandom(int matriz[11][21]);

void imprimitMatriz(int matriz[11][21]);

void limpiarMatriz(int resultado[11][21]);

void asignarColores(int matriz[11][21]);

void mostrarBT(int resultado[11][21], int matriz[11][21]);

bool flag = true;//Para ver cual ventana se abre si el BP game o el Puzzle

int cantObs = 1;//Cantidad de obstaculos

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
		sf::RenderWindow obstaculos(sf::VideoMode(400, 200), "Cauantos Obstaculos");
		sf::String playerInput;
		sf::Text playerText;

		///////////////////////////////////////////////////////////////////////
		//El programa sigue corriendo siemrpre y cuando la ventana este abierta
		while (obstaculos.isOpen())
		{

			//Revisa todos los eventos que se activaron desde la ultima iteracion 
			sf::Event event;
			while (obstaculos.pollEvent(event))
			{
				//Se cierra la ventana
				if (event.type == sf::Event::Closed)
					obstaculos.close();

				if (event.type == sf::Event::TextEntered)
				{
					playerInput += event.text.unicode;
					playerText.setString(playerInput);
				}
			}
			obstaculos.clear(sf::Color::White);
			obstaculos.draw(playerText);
			obstaculos.display();
		}
		/////////////////////////////////////////////////////////////////////

		sf::RenderWindow ventanaPrueba(sf::VideoMode(1400, 800), "My window");
		const int chanchaDim = 60; //Dimensiones de la cancha
		sf::RectangleShape cuadrados(sf::Vector2f(chanchaDim, chanchaDim));

		const int tamanoCancha = 22;//Cantidad maxima de cuadrados que puede haber por fila y columna

		vector<vector<RectangleShape>> cuadradosCancha;//En ese vector se almacenan los cuadrados de la cancha

		cuadradosCancha.resize(tamanoCancha, vector<sf::RectangleShape>());

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

		asignarColores(cuadrosCancha2);

		////Src(source) es el inicio del pathfinding
		//Pair src(5, 10);

		////Dest muestra el destino del pathfinding
		//Pair dest(5, 19);

		//PF.aStarSearch(cuadrosCancha2, src, dest);

		BT.hallarCamino(cuadrosCancha2, 5, 10, 5, 1, resultado);

		mostrarBT(resultado, cuadrosCancha2);

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

		// run the program as long as the window is open
		while (ventanaPrueba.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (ventanaPrueba.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					ventanaPrueba.close();

				ventanaPrueba.clear(sf::Color(255, 255, 255));

				for (int x = 0; x < 11; x++)
				{
					for (int y = 0; y < 21; y++)
					{
						ventanaPrueba.draw(cuadradosCancha[x][y]);
					}
				}

				ventanaPrueba.display();
			}
		}
	}else {
	/*
	* AQUI HAY QUE PONER EL CODIGO DEL PUZZLE GAME
	*/
	}
}


//Esta funciona elige las posiciones de los judagores o obstaculos aleatoriamente
void numerosRandom(int matriz[11][21]) {
	srand(time(NULL)); //Numeros aleatorios


	int filas[9], columnas[9], num = 1;

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
	for (int x = 0; x < 9; x++)
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

void asignarColores(int matriz[11][21])
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

