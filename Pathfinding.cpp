#include "Pathfinding.h"


//Revisa si el numero de celda se encuentra dentro de los parametros de la matriz
bool Pathfinding::isValid(int matriz[11][21], const Pair& point)
{	// Returns true if row number and column number is in range
	//Retorna verdadero si el numero de la fila y la columna esta dentro del rango
	if (11 > 0 && 21 > 0)
		return (point.first >= 0) && (point.first < 11) && (point.second >= 0) && (point.second < 21);
	return false;
}


//Esta funcion revisa si la celda esta bloqueada o no
bool Pathfinding::isUnBlocked(int matriz[11][21], const Pair& point)
{

	//Regresa verdadero si la celda no esta bloqueada en el caso contrario falso
	return isValid(matriz, point) && matriz[point.first][point.second] == 0;
}


//Esta funcion revisa si el punto actual es el destino o no
bool Pathfinding::isDestination(const Pair& position, const Pair& dest)
{
	return position == dest;
}


//Calcula la heuristica "H"
double Pathfinding::calculateHValue(const Pair& src, const Pair& dest)
{

	return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
}


//Esta funcion imprime el camino hacia el destino en caso de que si haya
void Pathfinding::tracePath(const array<array<cell, 21>, 11>& cellDetails, const Pair& dest, int matriz[11][21])
{
	printf("\nEl camino es ");

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


//Esta funcion encuentra el camino mas corto entre un punto A y un punto B, utiliza el algoritmo A*
void Pathfinding::aStarSearch(int matriz[11][21], const Pair& src, const Pair& dest)
{

	//El punto de inicio esta fuera del rango
	if (!isValid(matriz, src)) {
		printf("El punto de inicio no es valido\n");
		return;
	}


	//El destino se encuentra afeura del ragno
	if (!isValid(matriz, dest)) {
		printf("Este destino no es valido\n");
		return;
	}


	//El camino de inicio o el destino estan bloqueados
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
	priority_queue<Tuple, vector<Tuple>, greater<Tuple> >openList;

	//Se agrega la celda inicial en la lista abierta y se declara como f = 0
	openList.emplace(0.0, i, j);


	while (!openList.empty()) {
		const Tuple& p = openList.top();

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


