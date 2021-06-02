#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Menu.h"

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

using namespace std;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[9]);

void numerosRandom(int matriz[11][21]);

void imprimitMatriz(int matriz[11][21]);

bool flag = true;//Para ver cual ventana se abre si el BP game o el Puzzle

int cantObs = 9;//Cantidad de obstaculos


//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// A C++ Program to implement A* Search Algorithm



// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for tuple<int, int, int> type
typedef tuple<double, int, int> Tuple; 

// A structure to hold the neccesary parameters
struct cell {
	// Row and Column index of its parent
	Pair parent;
	// f = g + h
	double f, g, h;
	cell()
		: parent(-1, -1)
		, f(-1)
		, g(-1)
		, h(-1)
	{
	}
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int matriz[11][21], const Pair& point)
{ // Returns true if row number and column number is in
// range
	if (11 > 0 && 21 > 0)
		return (point.first >= 0) && (point.first < 11) && (point.second >= 0) && (point.second < 21);

	return false;
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int matriz[11][21], const Pair& point)
{
	// Returns true if the cell is not blocked else false
	return isValid(matriz, point) && matriz[point.first][point.second] == 0;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(const Pair& position, const Pair& dest)
{
	return position == dest;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(const Pair& src, const Pair& dest)
{
	// h is estimated with the two points distance formula
	return sqrt(pow((src.first - dest.first), 2.0)
		+ pow((src.second - dest.second), 2.0));
}

// A Utility Function to trace the path from the source to
// destination
void tracePath(const array<array<cell, 21>, 11>& cellDetails, const Pair& dest, int matriz[11][21])
{
	printf("\nThe Path is ");

	stack<Pair> Path;

	int row = dest.first;
	int col = dest.second;
	matriz[row][col] = 4;
	Pair next_node = cellDetails[row][col].parent;
	do {
		Path.push(next_node);
		next_node = cellDetails[row][col].parent;
		row = next_node.first;
		col = next_node.second;
	} while (cellDetails[row][col].parent != next_node);

	Path.emplace(row, col);
	while (!Path.empty()) {
		Pair p = Path.top();
		Path.pop();
		cout << "MATRIZ: " << matriz[p.first][p.second] << endl;
		matriz[p.first][p.second] = 4;
		printf("-> (%d,%d) ", p.first, p.second);
		
	}
}

// A Function to find the shortest path between a given
// source cell to a destination cell according to A* Search
// Algorithm
void aStarSearch(int matriz[11][21], const Pair& src, const Pair& dest)
{
	// If the source is out of range
	if (!isValid(matriz, src)) {
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (!isValid(matriz, dest)) {
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	//
	if (!isUnBlocked(matriz, src) || !isUnBlocked(matriz, dest)) {
		printf("El \n");
		return;
	}

	//Si el destino es el mismo que el inicio
	if (isDestination(src, dest)) {
		printf("Este ya es el destino\n");
		return;
	}

	//Se crea la lista cerrada y se inizializa como falsa ya que ninguna celda se ha incluido
	bool closedList[11][21];
	memset(closedList, false, sizeof(closedList));

	//El arreglo contiene informacion acerca de las celdas
	array<array<cell, 21>, 11> cellDetails;

	int i, j;
	// Se inizializan los parametros de los nodos
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent = { i, j };

	//Se crea una lista abierta en donde van a ir las celdas que se van a visitar o que se esta visitando en el momento
	priority_queue<Tuple, vector<Tuple>,greater<Tuple> >openList;

	//Se agrega la celda inicial en la lista abierta y se declara como f = 0
	openList.emplace(0.0, i, j);

	
	while (!openList.empty()) {
		const Tuple& p = openList.top();
		// Add this vertex to the closed list
		i = get<1>(p); // Segundo elemento de la tupla
		j = get<2>(p); // Tercer elemento de la tupla


		openList.pop();
		closedList[i][j] = true;
		/*
				Norte	 (i-1, j)
				Sur	 (i+1, j)
				Este	 (i, j+1)
				Oeste		 (i, j-1)
				Noreste (i-1, j+1)
				Noroeste (i-1, j-1)
				Sureste (i+1, j+1)
				Suroeste (i+1, j-1)
		*/
		for (int add_x = -1; add_x <= 1; add_x++) {
			for (int add_y = -1; add_y <= 1; add_y++) {
				Pair neighbour(i + add_x, j + add_y);

				if (isValid(matriz, neighbour)) {
					//Si el destino es la misla celda que el el actual sucesor
					if (isDestination(
						neighbour,
						dest)) { // Se convierte en el partent de la celda del destino
						cellDetails[neighbour.first]
							[neighbour.second]
						.parent
							= { i, j };
						printf("The destination cell is "
							"found\n");
						tracePath(cellDetails, dest, matriz);
						return;
					}

					//Si el sucesor ya esta en la lista cerrada
					//o el lugar esta bloqueado se ignora y
					//se ejecuta lo siguente
					else if (!closedList[neighbour.first]
						[neighbour.second]
					&& isUnBlocked(matriz,
						neighbour)) {
						double gNew, hNew, fNew;
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(neighbour,
							dest);
						fNew = gNew + hNew;

						// Si no se encuentra en la lista abierta
						// se agrega a la lista. Convierte el cuadro actual
						// en el parent.
						if (cellDetails[neighbour.first]
							[neighbour.second]
						.f
							== -1
							|| cellDetails[neighbour.first]
							[neighbour.second]
						.f
		> fNew) {
							openList.emplace(
								fNew, neighbour.first,
								neighbour.second);

							cellDetails[neighbour.first]
								[neighbour.second]
							.g
								= gNew;
							cellDetails[neighbour.first]
								[neighbour.second]
							.h
								= hNew;
							cellDetails[neighbour.first]
								[neighbour.second]
							.f
								= fNew;
							cellDetails[neighbour.first]
								[neighbour.second]
							.parent
								= { i, j };
						}
					}
				}
			}
		}
	}
	printf("No se encontro la celda\n");
}

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

		//Src(source) es el inicio del pathfinding
		Pair src(5, 10);

		//Dest muestra el destino del pathfinding
		Pair dest(5, 19);

		aStarSearch(cuadrosCancha2, src, dest);

		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 21; y++)
			{
				if (cuadrosCancha2[x][y] == 1)
				{
					cuadradosCancha[x][y].setFillColor(Color::Blue);//El azul muestra los bordes del mapa 
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