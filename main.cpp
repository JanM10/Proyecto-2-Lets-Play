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

using namespace std;

//Menu ventana_nueva;
bool verificar(int num, int arreglo[9]);

void numerosRandom(int matriz[11][21]);

void imprimitMatriz(int matriz[11][21]);


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
	if (!isUnBlocked(matriz, src)
		|| !isUnBlocked(matriz, dest)) {
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src, dest)) {
		printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	bool closedList[11][21];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	// of that cell
	array<array<cell, 21>, 11> cellDetails;

	int i, j;
	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent = { i, j };

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implenented as a set of tuple.*/
	std::priority_queue<Tuple, std::vector<Tuple>,
		std::greater<Tuple> >
		openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.emplace(0.0, i, j);

	// We set this boolean value as false as initially
	// the destination is not reached.
	while (!openList.empty()) {
		const Tuple& p = openList.top();
		// Add this vertex to the closed list
		i = get<1>(p); // second element of tupla
		j = get<2>(p); // third element of tupla

		// Remove this vertex from the open list
		openList.pop();
		closedList[i][j] = true;
		/*
				Generating all the 8 successor of this cell
						N.W N N.E
						\ | /
						\ | /
						W----Cell----E
								/ | \
						/ | \
						S.W S S.E

				Cell-->Popped Cell (i, j)
				N --> North	 (i-1, j)
				S --> South	 (i+1, j)
				E --> East	 (i, j+1)
				W --> West		 (i, j-1)
				N.E--> North-East (i-1, j+1)
				N.W--> North-West (i-1, j-1)
				S.E--> South-East (i+1, j+1)
				S.W--> South-West (i+1, j-1)
		*/
		for (int add_x = -1; add_x <= 1; add_x++) {
			for (int add_y = -1; add_y <= 1; add_y++) {
				Pair neighbour(i + add_x, j + add_y);
				// Only process this cell if this is a valid
				// one
				if (isValid(matriz, neighbour)) {
					// If the destination cell is the same
					// as the current successor
					if (isDestination(
						neighbour,
						dest)) { // Set the Parent of
								// the destination cell
						cellDetails[neighbour.first]
							[neighbour.second]
						.parent
							= { i, j };
						printf("The destination cell is "
							"found\n");
						tracePath(cellDetails, dest, matriz);
						return;
					}
					// If the successor is already on the
					// closed list or if it is blocked, then
					// ignore it. Else do the following
					else if (!closedList[neighbour.first]
						[neighbour.second]
					&& isUnBlocked(matriz,
						neighbour)) {
						double gNew, hNew, fNew;
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(neighbour,
							dest);
						fNew = gNew + hNew;

						// If it isn’t on the open list, add
						// it to the open list. Make the
						// current square the parent of this
						// square. Record the f, g, and h
						// costs of the square cell
						//			 OR
						// If it is on the open list
						// already, check to see if this
						// path to that square is better,
						// using 'f' cost as the measure.
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

							// Update the details of this
							// cell
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

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destiantion cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	printf("Failed to find the Destination Cell\n");
}

//// Driver program to test above function
//int main()
//{
//	/* Description of the Grid-
//	1--> The cell is not blocked
//	0--> The cell is blocked */
//	array<array<int, 10>, 9> grid{
//		{ { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
//		{ { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 } },
//		{ { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 } },
//		{ { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 } },
//		{ { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 } },
//		{ { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 } },
//		{ { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 } },
//		{ { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
//		{ { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } } }
//	};
//
//	// Source is the left-most bottom-most corner
//	Pair src(8, 0);
//
//	// Destination is the left-most top-most corner
//	Pair dest(2, 2);
//
//	aStarSearch(grid, src, dest);
//
//	return 0;
//}

int main()
{

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

	/////////////////////////////////////////////////////////////////////
	sf::RenderWindow ventanaPrueba(sf::VideoMode(1400, 800), "My window");
	const int chanchaDim = 60; //Dimensiones de la cancha
	sf::RectangleShape cuadrados(sf::Vector2f(chanchaDim, chanchaDim));

	const int tamanoCancha = 22;

	vector<vector<RectangleShape>> cuadradosCancha;

	cuadradosCancha.resize(tamanoCancha, vector<sf::RectangleShape>());

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

	//0-8   0-18
	//array<array<int, 21>, 11>grid{     
	//	{{{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }},
	//	{{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }},
	//	{{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
	//	{{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }}} };

	int cuadrosCancha2[11][21]{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };


	numerosRandom(cuadrosCancha2);

	Pair src(1, 4);

	// Destination is the left-most top-most corner
	Pair dest(6, 19);

	aStarSearch(cuadrosCancha2, src, dest);

	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 21; y++)
		{
			if (cuadrosCancha2[x][y] == 1)
			{
				cuadradosCancha[x][y].setFillColor(Color::Blue);
			}
			else if (cuadrosCancha2[x][y] == 2) {
				cuadradosCancha[x][y].setFillColor(Color::Red);
			}
			else if (cuadrosCancha2[x][y] == 3) {
				cuadradosCancha[x][y].setFillColor(Color::Black);
			}
			else if (cuadrosCancha2[x][y] == 4){
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

}


//1-9    1-10
void numerosRandom(int matriz[11][21]) {
	srand(time(NULL)); //Numeros aleatorios

	//####################################################################
	//Cambiar el nueve por el numero random que pida el profe de obstaculos
	//####################################################################
	int filas[9], columnas[9], num = 1;
	int cantObs = 9;//Cantidad de obstaculos

	for (int i = 9; i > abs(cantObs-9); i--)
	{
		filas[i-1] = 0;
		columnas[i-1] = 0;
	}

	//####################################################################
	//Cambiar el nueve por el numero random que pida el profe de obstaculos
	//####################################################################
	//Para que no se repitan los numeros de filas
	for (int i = 0; i < cantObs; i++)
	{
		while (verificar(num, filas) && num != 0) {

			num = 1 + rand() % (9);
			
		}
		filas[i] = num;
	}


	//####################################################################
	//Cambiar el nueve por el numero random que pida el profe de obstaculos
	//####################################################################
	//Para que no se repitan los numeros de columnas
	for (int i = 0; i < cantObs; i++)
	{
		while (verificar(num, columnas) && num != 0) {

			num = 1 + rand() % (9);
		}
		columnas[i] = num;
	}


	//####################################################################
	//Cambiar el nueve por el numero random que pida el profe de obstaculos
	//####################################################################
	// 20-#columna
	for (int x = 0; x < 9; x++)
	{
		matriz[filas[x]][columnas[x]] = 1;
		matriz[filas[x]][20-columnas[x]] = 1;
	}


	imprimitMatriz(matriz);

}

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




