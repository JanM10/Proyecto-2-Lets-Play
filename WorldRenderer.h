#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H
#include <SFML/Graphics.hpp>
#include "World.h"

class WorldRenderer {

public:
	WorldRenderer(World& world);
	~WorldRenderer();

	void render(sf::RenderWindow& ventana) const;
	void renderBalls(sf::RenderWindow& ventana) const;

private:
	World& world;
};

#endif