#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World& world) : world(world) {}

WorldRenderer::~WorldRenderer() {}

void WorldRenderer::render(sf::RenderWindow& ventana) const {
	renderBalls(ventana);
}

void WorldRenderer::renderBalls(sf::RenderWindow& ventana) const {
	for (Ball ball : world.getBalls()) {
		ball.draw(ventana);
	}
}