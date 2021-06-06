#ifndef WORLD_H
#define WORLD_H
#include "Ball.h"
#include "Collision.h"

class World {
public:
	World();
	~World();

	void initBalls(size_t size);
	void update(float deltatime);

	bool dragBall(sf::Vector2f point);
	void setDraggedVelocity(float x, float y);

	Ball* getDraggedBall() const;
	std::vector<Ball> getBalls() const;

private:
	std::vector<Ball> balls;

	Ball* draggedBall;

	Collision collision;
};

#endif
