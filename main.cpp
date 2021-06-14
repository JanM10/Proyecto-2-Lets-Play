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

#include <fstream>

//Instancias de las clases Backtracking y Pathfinding
Backtracking BT;
Pathfinding PF;
ofstream archivo;
ofstream archivo2;
ofstream archivo3;

using namespace std;

//Declaracion de funciones
bool verificar(int num, int arreglo[9]);

void numerosRandom(int matriz[11][21]);

void imprimitMatriz(int matriz[11][21]);

void limpiarMatriz(int resultado[11][21]);

void asignarColores(int cuadrosCancha2[11][21]);

void mostrarBT(int resultado[11][21], int matriz[11][21]);

//Declaracion de variables publicas
const int tamanoCancha = 22;//Cantidad maxima de cuadrados que puede haber por fila y columna

bool flag = true;//Para ver cual ventana se abre si el BP game o el Puzzle

int cantObs;//Cantidad de obstaculos

int compuGoles = 0, jugadorGoles = 0;//Cantidad de goles

bool jugador = true;//Turno del jugador o computadora

int contador = 1;//Contador para el turno del jugador o computadora

int resultado[11][21]{ //Matriz para el backtracking
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


int colores[11][21]{ //Matriz de respaldo
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

int posicionesX[18];

int posicionesY[18];

typedef pair<int, int> Pair;

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

	//Si el flag es falso se abre la ventana del BP Game en caso contrario abre el Puzzle game
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

		//En esta ventana el usuario puede escribir la cantidad de jugadores que desea poner en la cancha
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


		sf::RenderWindow ventanaPrueba(sf::VideoMode(1400, 800), "BP Game");

		//////////////////////////////////////////////////////////////
		//Textos que van en pantalla
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
		///////////////////////////////////////////////////////////////////

		const int chanchaDim = 60; //Dimensiones de la cancha
		sf::RectangleShape cuadrados(sf::Vector2f(chanchaDim, chanchaDim));
		ventanaPrueba.setFramerateLimit(120);
		
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

		numerosRandom(cuadrosCancha2);//Se asignan los obstaculos en pantalla

		archivo3.open("booleano.txt");
		archivo3 << "";
		archivo3.close();
	
		//Se abre la ventana del BP GAME
		while (ventanaPrueba.isOpen())
		{
			deltatime = clock.restart().asSeconds();

			sf::Event event;
			while (ventanaPrueba.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					ventanaPrueba.close();
				
				switch (event.type) {

				case sf::Event::KeyReleased:
					switch (event.key.code) 
					{
						case sf::Keyboard::C:
							jugador = false;
							contador++;
							archivo3.open("booleano.txt");
							archivo3 << "true";
							archivo3.close();
							break;
					}

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left && contador%2 != 0) {
						sf::Vector2i point = sf::Mouse::getPosition(ventanaPrueba);

						if (world.dragBall(sf::Vector2f((float)point.x, (float)point.y))) {
							dragging = true;
						}

					}
					break;

				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left && contador % 2 != 0) {

						world.setDraggedVelocity(line[1].position.x, line[1].position.y);
						dragging = false;
					}
					break;
				}
				
				
			}
			ventanaPrueba.clear(sf::Color::Black);

			int posX = (worldRenderer.getPositionX(ventanaPrueba) / 60) - 1;
			int posY = (worldRenderer.getPositionY(ventanaPrueba) / 60) - 1;

			//Si la velocidad del balon es igual o menor que cero, se hace el calculo del backtracking o el pathfinding
			if (worldRenderer.getVelocityX(ventanaPrueba) <= 2 && worldRenderer.getVelocityY(ventanaPrueba) <= 2
				|| worldRenderer.getVelocityX(ventanaPrueba) == 0 && worldRenderer.getVelocityY(ventanaPrueba) == 0)
			{
				worldRenderer.getPositionX(ventanaPrueba);
				worldRenderer.getPositionY(ventanaPrueba);

				worldRenderer.setVelocity(ventanaPrueba, 0, 0);

				//cout << "X: " << posX << " " << "Y: " << posY << endl;

				asignarColores(cuadrosCancha2);

				limpiarMatriz(resultado);

				if (jugador && contador%2 != 0)
				{

					//Src(source) es el inicio del pathfinding
					Pair src(posY, posX); //Pair src(5, 10);

					//Dest muestra el destino del pathfinding
					Pair dest(5, 19);

					PF.aStarSearch(cuadrosCancha2, src, dest);


				}
				else
				{
					//Se envia la posicion de inicio y de fin al backtracking
					BT.hallarCamino(cuadrosCancha2, posY, posX, 5, 1, resultado);

					//Se calcula la ruta utilizando backtraking
					mostrarBT(resultado, cuadrosCancha2);

					jugador = true;
				}

				//system("cls");
			
			}


			//Se le asignas los colores a la cancha
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 21; y++)
				{
					if (cuadrosCancha2[x][y] == 0)
					{
						cuadradosCancha[x][y].setFillColor(Color::Green);//El azul muestra los obstaculos del mapa 
					}
					else if (cuadrosCancha2[x][y] == 1)
					{
						cuadradosCancha[x][y].setFillColor(Color::Blue);//El azul muestra los obstaculos del mapa 
					}
					else if (cuadrosCancha2[x][y] == 2) 
					{
						cuadradosCancha[x][y].setFillColor(Color::Red);//El rojo muestra las porterias
					}
					else if (cuadrosCancha2[x][y] == 3) 
					{
						cuadradosCancha[x][y].setFillColor(Color::Black);//El negro muestra los bordes del mapa
					}
					else if (cuadrosCancha2[x][y] == 4) //El color blanco representa la ruta del pathfinding
					{
						cuadradosCancha[x][y].setFillColor(Color::White);
					}
				}
			}


			archivo.open("rutas.txt");
			archivo2.open("rutas2.txt");
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 21; y++)
				{
					if (cuadradosCancha[x][y].getFillColor() == Color::Blue)
					{
						archivo << to_string((int)cuadradosCancha[x][y].getPosition().x) + "\n";
						archivo2 << to_string((int)cuadradosCancha[x][y].getPosition().y) + "\n";
					}
				}
			}
			archivo.close();
			archivo2.close();
			
			
			//Se guardan las posiciones exactas de los obstaculos para las colosiones

			//for (int i = 0; i < 18; i++)
			//{
			//	cout << endl;
			//	cout << "POSX: " << posicionesX[i] << endl;
			//	cout << "POSY: " << posicionesY[i] << endl;
			//}


			
			//Se muestra toda la cancha en pantalla
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 21; y++)
				{
					ventanaPrueba.draw(cuadradosCancha[x][y]);
				}
			}

			//Muestra en pantalla hacia donde se jala el balon
			if (dragging) {
				sf::Vector2i point = sf::Mouse::getPosition(ventanaPrueba);

				line[0] = sf::Vertex(sf::Vector2f(world.getDraggedBall()->getPosition()), sf::Color::Blue);
				line[1] = sf::Vertex(sf::Vector2f((float)point.x, (float)point.y), sf::Color::Blue);
				
			}
			if (dragging) {
				ventanaPrueba.draw(line, 2, sf::Lines);
			}

			//Se nuestra la pantalla del ganador
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

			//Se suma un gol y se muestra en pantalla
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


			//Todo lo que se muestra en pantalla
			worldRenderer.render(ventanaPrueba);
			ventanaPrueba.draw(marcador);
			ventanaPrueba.draw(textoCompu);
			ventanaPrueba.draw(textoJugador);
			ventanaPrueba.display();
			world.update(deltatime);
		}

	}
	else {

	sf::RenderWindow puzzle(sf::VideoMode(600, 200), "Puzzle Game");

	bool openPuzzle;
	int image;
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	Textbox playerInput(15, sf::Color::White, true);

	playerInput.setFont(arial);
	playerInput.setPosition({ 100, 100 });
	playerInput.setLimit(true, 1);


	Textbox string(15, sf::Color::White, false);

	string.setString("Escriba de cuanto quiere el puzzle \n (el numero que ingrese sera de una matriz de n x n, siendo n el numero ingresado; \n solo hay matrices de 2, 3 ,4 y 5)");
	string.setFont(arial);
	string.setPosition({ 10, 10 });

	Textbox warning(15, sf::Color::Red, false);

	warning.setString("Solo se pueden elegir matrices de 2x2, 3x3, 4x4 o 5x5");
	warning.setFont(arial);
	warning.setPosition({ 10, 1000 });


	///////////////////////////////////////////////////////////////////////
	//El programa sigue corriendo siempre y cuando la ventana este abierta
	while (puzzle.isOpen())
	{

		//Revisa todos los eventos que se activaron desde la ultima iteracion 
		Event event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			image = playerInput.getText().front() - 48;
			if (image > 6 || image < 2) {
				warning.setPosition({ 10, 65 });
			}
			else {
				openPuzzle = true;
				puzzle.close();
			}

		}
		while (puzzle.pollEvent(event)) {

			//Se cierra la ventana
			switch (event.type)
			{
			case sf::Event::Closed:
				openPuzzle = false;
				puzzle.close();

			case::Event::TextEntered:
				playerInput.typedOn(event);
			}


		}

		puzzle.clear();
		string.drawTo(puzzle);
		warning.drawTo(puzzle);
		playerInput.drawTo(puzzle);
		puzzle.display();
	}
	////////

	if (openPuzzle) {

		RenderWindow app(VideoMode(600, 600), "Genetic Puzzle!");
		app.setFramerateLimit(60);
		int gridSize = 0;



		Texture t;
		if (image == 2) {
			t.loadFromFile("images/2x2.png");
			gridSize = 2;
		}
		if (image == 3) {
			t.loadFromFile("images/3x3.png");
			gridSize = 3;
		}
		if (image == 4) {
			t.loadFromFile("images/4x4.png");
			gridSize = 4;
		}
		if (image == 5) {
			t.loadFromFile("images/red.png");
			gridSize = 5;
		}
		if (image == 6) {
			t.loadFromFile("images/smiley.png");
			gridSize = 4;
		}

		int grid[7][7];
		Sprite sprite[25];
		memset(grid, -1, sizeof(int) * (gridSize + 2) * (gridSize + 2)); // initialize array to -1
		int w = 64;


		//vector<vector<RectangleShape>> cuadradosCancha;//En ese vector se almacenan los cuadrados de la cancha

		//cuadradosCancha.resize(tamanoCancha, vector<sf::RectangleShape>());

		// initialize puzzle
		int n = 0;
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				sprite[n].setTexture(t);
				sprite[n].setTextureRect(IntRect(j * w, i * w, w, w));
				grid[i + 1][j + 1] = n;
				n++;
			}
		}

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
						int x = pos.y / w + 1;
						int y = pos.x / w + 1;
						int dx = 0;
						int dy = 0;

						if (grid[x + 1][y] == ((gridSize * gridSize) - 1)) { dx = 1; }
						if (grid[x - 1][y] == (gridSize * gridSize) - 1) { dx = -1; }
						if (grid[x][y + 1] == (gridSize * gridSize) - 1) { dy = 1; }
						if (grid[x][y - 1] == (gridSize * gridSize) - 1) { dy = -1; }

						// exchange blank and grid
						int n = grid[x][y];
						grid[x][y] = ((gridSize * gridSize) - 1);
						grid[x + dx][y + dy] = n;

					}

			}

			app.clear(Color::Color(82, 82, 82));
			for (int i = 0; i < gridSize; i++)
				for (int j = 0; j < gridSize; j++)
				{
					int n = grid[i + 1][j + 1];
					sprite[n].setPosition(j * w, i * w);
					app.draw(sprite[n]);
				}

			app.display();

		}

	}
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

		colores[filas[x]][columnas[x]] = 1;
		colores[filas[x]][20 - columnas[x]] = 1;
	}

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
}

//Asigna los valores de la matriz de respaldo a la original
void asignarColores(int cuadrosCancha2[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			cuadrosCancha2[i][j] = colores[i][j];
		}
	}
}

//Se muestra los datos del backtracking
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


