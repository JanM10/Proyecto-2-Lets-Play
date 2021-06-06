#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World& world) : world(world) {}

WorldRenderer::~WorldRenderer() {}

void WorldRenderer::render(sf::RenderWindow& ventanaPrueba) const {
	renderBalls(ventanaPrueba);
}

void WorldRenderer::renderBalls(sf::RenderWindow& ventanaPrueba) const {
	for (Ball ball : world.getBalls()) {
		ball.draw(ventanaPrueba);
	}
}