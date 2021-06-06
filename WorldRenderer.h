#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H
#include <SFML/Graphics.hpp>
#include "World.h"

class WorldRenderer {

public:
	WorldRenderer(World& world);
	~WorldRenderer();

	void render(sf::RenderWindow& ventanaPrueba) const;
	void renderBalls(sf::RenderWindow& ventanaPrueba) const;

private:
	World& world;
};

#endif