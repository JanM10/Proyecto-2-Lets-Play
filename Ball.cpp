#include "Ball.h"
#include "Matriz.h"

Matriz Obs;
int k = 0;

Ball::Ball(float radius) : dragged(false), mass(radius * 20.f), circleShape(sf::CircleShape(radius)) {
	circleShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	circleShape.setOrigin(radius, radius);
}

Ball::~Ball() {}

void Ball::update(float deltatime) {
	setAcceleration(-getVelocity().x * 0.9f * deltatime, -getVelocity().y * 0.9f * deltatime);
	setVelocity(getVelocity().x + (getAcceleration().x), getVelocity().y + (getAcceleration().y));

	circleShape.move(getVelocity());

	if (getVelocity().x <= 0.01 && getVelocity().y <= 0.01)
	{
		//cout << "Se detuvo" << endl;
		setLado(0);
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

	//for (int i = 0; i < 18; i++)
	//{
	//	cout << "X: " << Obs.getPositionX(i) << endl;
	//	cout << "Y: " << Obs.getPositionY(i) << endl;
	//}
	Obs.setObsPos();
	for (int i = 0; i < 18; i++)
	{
		//if (getBounds().intersects(Obs.cuadradosCancha[1][1].getGlobalBounds()))
		//if (getPosition().x >= Obs.getPositionX(i) - 60 + getRadius() &&
		//	getPosition().x <= Obs.getPositionX(i) + getRadius() &&
		//	getPosition().y <= Obs.getPositionY(i) - 60 - getRadius() &&
		//	getPosition().y <= Obs.getPositionY(i) - getRadius())
		//{

		if (getPosition().x < Obs.getPositionX(i) + getRadius()) {//Borde izquierdo
			setPosition(Obs.getPositionX(i) + getRadius(), getPosition().y);
			setVelocity(-getVelocity().x, getVelocity().y);
		}


			//if (Obs.getPositionX(i) >= getPosition().x &&  //arriba
			//	Obs.getPositionX(i) <= getPosition().x &&
			//	Obs.getPositionY(i) >= getPosition().y &&
			//	Obs.getPositionY(i) <= getPosition().y)
			//{
			//	setPosition(getPosition().x, Obs.getPositionY(i) + getRadius());

			//	setVelocity(-getVelocity().x, getVelocity().y);
			//	cout << endl;
			//	cout << "CHOCA Arriba" << endl;
			//}

			//if (Obs.getPositionX(i) >= getPosition().x &&  //izquierda
			//	Obs.getPositionX(i) <= getPosition().x &&
			//	Obs.getPositionY(i) >= getPosition().y &&
			//	Obs.getPositionY(i) <= getPosition().y)
			//{

			//	setPosition(Obs.getPositionX(i) + getRadius(), getPosition().y);

			//	setVelocity(-getVelocity().x, getVelocity().y);
			//	cout << endl;
			//	cout << "CHOCA izquierda" << endl;
			//}

			//if (Obs.getPositionX(i) >= getPosition().x &&  //derecha
			//	Obs.getPositionX(i) <= getPosition().x &&
			//	Obs.getPositionY(i) >= getPosition().y &&
			//	Obs.getPositionY(i) <= getPosition().y)
			//{

			//	setPosition(Obs.getPositionX(i) - getRadius(), getPosition().y);

			//	setVelocity(-getVelocity().x, getVelocity().y);
			//	cout << endl;
			//	cout << "CHOCA derecha " << endl;
			//}
			//if (Obs.getPositionX(i) >= getPosition().x &&  //dol
			//	Obs.getPositionX(i) <= getPosition().x &&
			//	Obs.getPositionY(i) >= getPosition().y &&
			//	Obs.getPositionY(i) <= getPosition().y)

			//{

			//	setPosition(getPosition().x, Obs.getPositionY(i) - getRadius());

			//	setVelocity(getVelocity().x, -getVelocity().y);
			//	cout << endl;
			//	cout << "CHOCA Abajo" << endl;
			//}


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

sf::FloatRect Ball::getBounds() const
{
	return circleShape.getGlobalBounds();
}

void Ball::setObsPos()
{
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 21; y++)
		{
			if (cuadradosCancha[x][y].getFillColor() == sf::Color::Blue)
			{
				cout << endl;
				posicionesX[k] = cuadradosCancha[x][y].getPosition().x;
				cout << "POSX: " << posicionesX[k] << endl;
				posicionesY[k] = cuadradosCancha[x][y].getPosition().y;
				cout << "POSY: " << posicionesY[k] << endl;
				k++;
			}
		}
	}
	k = 0;
}

void Ball::setResize()
{
	cuadradosCancha.resize(60, vector<sf::RectangleShape>());
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
