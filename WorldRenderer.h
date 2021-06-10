#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H
#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>

using namespace std;

class WorldRenderer {

public:
	WorldRenderer(World& world);
	~WorldRenderer();

	void render(sf::RenderWindow& ventanaPrueba) const;
	void renderBalls(sf::RenderWindow& ventanaPrueba) const;
	int getLado(sf::RenderWindow& ventanaPrueba) const;
	void setLado(sf::RenderWindow& ventanaPrueba);

	int getPositionX(sf::RenderWindow& ventanaPrueba) const;
	int getPositionY(sf::RenderWindow& ventanaPrueba) const;

	float getVelocityX(sf::RenderWindow& ventanaPrueba) const;
	float getVelocityY(sf::RenderWindow& ventanaPrueba) const;

	void setVelocity(sf::RenderWindow& ventanaPrueba, float x, float y) const;

	float getRadius(sf::RenderWindow& ventanaPrueba) const;

	void setPosition(sf::RenderWindow& ventanaPrueba, int x, int y) const;

	sf::FloatRect getGlobalBounds(sf::RenderWindow& ventanaPrueba) const;

private:
	World& world;
};

#endif