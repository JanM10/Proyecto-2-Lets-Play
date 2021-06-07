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

void WorldRenderer::getPosition(sf::RenderWindow& ventanaPrueba) const{

	for (Ball ball : world.getBalls()) {
		cout << "X: " << ((int)(ball.getPosition().x/60))-1 << " " << "Y: " << ((int)ball.getPosition().y/60)-1 << endl;
	}
}

int WorldRenderer::getLado(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getLado();
	}
}

void WorldRenderer::setLado(sf::RenderWindow& ventanaPrueba)
{
	for (Ball ball : world.getBalls()) {
		ball.setLado(0);
	}
}


