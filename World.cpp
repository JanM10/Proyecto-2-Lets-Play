#include "World.h"

//Constructor
World::World() {
	draggedBall = nullptr;
	initBalls(1);
}

//Destructor
World::~World() {
	delete draggedBall;
}

//Se inicializan los balones
void World::initBalls(size_t size) {
	for (size_t i = 0; i < size; ++i) {

		float x = 690;
		float y = 390;
		float radius = 25;

		Ball ball = Ball(radius);
		ball.setPosition(x, y);

		balls.push_back(ball);
	}
}


//Se refresca el tiempo
void World::update(float deltatime) {
	for (Ball& ball : balls) {
		ball.update(deltatime);
	}
}

//Muestra si el balon se esta jalando o no
bool World::dragBall(sf::Vector2f point) {
	for (Ball& ball : balls) {
		if (collision.ballPointOverlap(sf::Vector2f(point.x, point.y), ball)) {
			draggedBall = &ball;
			return true;
		}
	}
	return false;
}

//Muestra la velocidad con que se esta jalando el balon
void World::setDraggedVelocity(float x, float y) {
	if (draggedBall) {
		draggedBall->setVelocity((draggedBall->getPosition().x - x) / 100,
			(draggedBall->getPosition().y - y) / 100);

		draggedBall = nullptr;
	}
}

//Devuelve hacia donde se jala el balon
Ball* World::getDraggedBall() const {
	return draggedBall;
}

//Devuelve el balon
std::vector<Ball> World::getBalls() const {
	return balls;
}