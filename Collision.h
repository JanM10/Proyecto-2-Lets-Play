#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Collision {
public:
	Collision();
	~Collision();

	bool ballOverlap(Ball ball, Ball ball2);
	bool ballPointOverlap(sf::Vector2f point, Ball ball);
	float distanceSquared(sf::Vector2f a, sf::Vector2f b);

};

#endif

