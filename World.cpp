#include "World.h"

World::World() {
	draggedBall = nullptr;
	initBalls(5);
}

World::~World() {
	delete draggedBall;
}

void World::initBalls(size_t size) {
	for (size_t i = 0; i < size; ++i) {

		float x = 700;
		float y = 400;
		float radius = 25;

		Ball ball = Ball(radius);
		ball.setPosition(x, y);

		balls.push_back(ball);
	}
}

void World::update(float deltatime) {
	for (Ball& ball : balls) {
		ball.update(deltatime);
	}
}


bool World::dragBall(sf::Vector2f point) {
	for (Ball& ball : balls) {
		if (collision.ballPointOverlap(sf::Vector2f(point.x, point.y), ball)) {
			draggedBall = &ball;
			return true;
		}
	}
	return false;
}

void World::setDraggedVelocity(float x, float y) {
	if (draggedBall) {
		draggedBall->setVelocity((draggedBall->getPosition().x - x) / 100,
			(draggedBall->getPosition().y - y) / 100);

		draggedBall = nullptr;
	}
}

Ball* World::getDraggedBall() const {
	return draggedBall;
}

std::vector<Ball> World::getBalls() const {
	return balls;
}