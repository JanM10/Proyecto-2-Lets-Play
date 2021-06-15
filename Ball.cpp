#include "Ball.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
ifstream archivo;
ifstream archivo2;
ifstream archivo3;
ofstream archivo4;

//Constructor del balon 
Ball::Ball(float radius) : dragged(false), mass(radius * 20.f), circleShape(sf::CircleShape(radius)) {
	circleShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	circleShape.setOrigin(radius, radius);
}

//Destructor del balon
Ball::~Ball() {}

//Actuliza el status del balon 
void Ball::update(float deltatime) { 
	setAcceleration(-getVelocity().x * 0.9f * deltatime, -getVelocity().y * 0.9f * deltatime);
	setVelocity(getVelocity().x + (getAcceleration().x), getVelocity().y + (getAcceleration().y));

	circleShape.move(getVelocity());

	if (getVelocity().x <= 0.01 && getVelocity().y <= 0.01)
	{
		setLado(0);
	}

	//Se detecta si es el turno de la computadora o del jugador
	archivo3.open("booleano.txt");
	string flag = "";
	string temp;
	while (archivo3 >> temp)
	{
		flag = temp;
	}
	archivo3.close();

	if (flag == "true")
	{
		archivo4.open("booleano.txt");
		archivo4 << "";
		flag = "false";
		archivo4.close();
		Sleep(3000);

		srand(time(NULL)); //Numeros aleatorios
		int x = 3 + (rand() % 6);
		int y = (rand() % 4) -2;
		cout << "X: " << x << endl;
		cout << "Y: " << y << endl;
		setVelocity(x,y);
	}



	//Porteria izquierda
	if (getPosition().x >= 60 + getRadius() && getPosition().x <= 120 + getRadius() &&
		getPosition().y >= 330 - getRadius() && getPosition().y <= 480 - getRadius()) {
		int gol = 1;
		setLado(gol);
		setPosition(700, 400);
		setVelocity(0, 0);
	}
	//Porteria derecha
	else if (getPosition().x >= 1200 + getRadius() && getPosition().x <= 1260 + getRadius() && getPosition().y >= 300 - getRadius() && getPosition().y <= 480 - getRadius()) {
		int gol = 2;
		setLado(gol);
		setPosition(700, 400);
		setVelocity(0, 0);
	}

	//Bordes del mapa
	if (getPosition().x < 120 + getRadius()) {//Borde izquierdo
		setPosition(120 + getRadius(), getPosition().y);
		setVelocity(-getVelocity().x, getVelocity().y);
	}
	else if (getPosition().x > 1260 - getRadius()) {//Borde derecho
		setPosition(1260 - getRadius(), getPosition().y);
		setVelocity(-getVelocity().x, getVelocity().y);
	}

	if (getPosition().y < 120 + getRadius()) {//Borde superior
		setPosition(getPosition().x, 120 + getRadius());
		setVelocity(getVelocity().x, -getVelocity().y);
	}
	else if (getPosition().y > 660 - getRadius()) {//Borde inferior
		setPosition(getPosition().x, 660 - getRadius());
		setVelocity(getVelocity().x, -getVelocity().y);
	}

	//Se agarran los puntos especificos donde se encuentran los obstaculos
	archivo.open("rutas.txt");
	archivo2.open("rutas2.txt");
	string texto;
	int number;
	int number2;
	int k = 0;
	while (archivo >> number && archivo2 >> number2)
	{
		this->posicionesX[k] = number;
		cout << "X: " << this->posicionesX[k] << endl;
		this->posicionesY[k] = number2;
		cout << "Y: " << this->posicionesY[k] << endl;
		k++;
	}
	archivo.close();

	//Este for se encarga de verificar si el balon choca contra alguno de los obstaculos y hace que rebote
	for (int i = 0; i < 18; i++)
	{
			//Arriba
			if (getPosition().x >= this->posicionesX[i] && getPosition().x <= this->posicionesX[i] + 60 &&
				getPosition().y + getRadius() >= this->posicionesY[i] && getPosition().y - getRadius() <= this->posicionesY[i] + 60)
			{
				setVelocity(getVelocity().x, -getVelocity().y);
			}
			
			//Abajo
			if (getPosition().x + getRadius() >= this->posicionesX[i] && getPosition().x + getRadius() <= this->posicionesX[i] + 60 &&
				getPosition().y + getRadius() >= this->posicionesY[i] && getPosition().y + getRadius() <= this->posicionesY[i])
			{
				setVelocity(getVelocity().x, -getVelocity().y);
			}

			//Izquierda/Lewy
			if (getPosition().x + getRadius() >= this->posicionesX[i] && getPosition().x - getRadius() <= this->posicionesX[i] + 60 && 
				getPosition().y >= this->posicionesY[i] && getPosition().y <= this->posicionesY[i] + 60)
			{
				setVelocity(-getVelocity().x, getVelocity().y);
			}

			//Derecha/Dewy
			if (getPosition().x + getRadius() >= this->posicionesX[i] && getPosition().x + getRadius() <= this->posicionesX[i] && 
				getPosition().y + getRadius() >= this->posicionesY[i] && getPosition().y + getRadius() <= this->posicionesY[i] + 60)
			{
				setVelocity(-getVelocity().x, getVelocity().y);
			}

			//// Esquinas
			//if (((int)(getPosition().x + getRadius())) == this->posicionesX[i] && ((int)(getPosition().y + getRadius())) == this->posicionesY[i])
			//{
			//	setVelocity(-getVelocity().x, -getVelocity().y);
			//}

			//if (((int)(getPosition().x + getRadius())) == this->posicionesX[i] + 60 && ((int)(getPosition().y + getRadius())) == this->posicionesY[i])
			//{
			//	setVelocity(-getVelocity().x, -getVelocity().y);
			//}

			//if (((int)(getPosition().x + getRadius())) == this->posicionesX[i] && ((int)(getPosition().y + getRadius())) == this->posicionesY[i] + 60)
			//{
			//	setVelocity(-getVelocity().x, -getVelocity().y);
			//}
			//if (((int)(getPosition().x + getRadius())) == this->posicionesX[i] + 60 && ((int)(getPosition().y + getRadius())) == this->posicionesY[i] + 60)
			//{
			//	setVelocity(-getVelocity().x, -getVelocity().y);
			//}
	}

}

//Se dibuja el balon
void Ball::draw(sf::RenderWindow& window) {
	window.draw(circleShape);
}

//Se asigna una posicion al balon
void Ball::setPosition(float x, float y) {
	this->circleShape.setPosition(sf::Vector2f(x, y));
}

//Devuelve el radio del balon
float Ball::getRadius() const {
	return circleShape.getRadius();
}

//Devuelve la posicion del balon
sf::Vector2f Ball::getPosition() const {
	return circleShape.getPosition();
}

//Devuelve el lado donde se metio el gol
int Ball::getLado() const
{
	return lado;
}

//Se asigna un lado donde se haya metido el gol
void Ball::setLado(int gol)
{
	lado = gol;
}

//Regresa los bordes del balon
sf::FloatRect Ball::getBounds() const
{
	return circleShape.getGlobalBounds();
}

//Se asigna una velocidad
void Ball::setVelocity(float x, float y) {
	this->velocity = sf::Vector2f(x, y);
}

//Se asigna una aceleracion
void Ball::setAcceleration(float x, float y) {
	this->acceleration = sf::Vector2f(x, y);
}

//Se asigna el poder jalar el balon
void Ball::setDragged(bool dragged) {
	this->dragged = dragged;
}

//Devuelve la masa
float Ball::getMass() const {
	return mass;
}

//Devuelve si se esta jalando el balon o no
float Ball::getDragged() const {
	return dragged;
}

//Devuelve la velocidad
sf::Vector2f Ball::getVelocity() const {
	return velocity;
}

//Devuelve la aceleracion
sf::Vector2f Ball::getAcceleration() const {
	return acceleration;
}
