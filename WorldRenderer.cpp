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

int WorldRenderer::getPositionX(sf::RenderWindow& ventanaPrueba) const{

	for (Ball ball : world.getBalls()) {
		return (int)ball.getPosition().x;
	}
}

int WorldRenderer::getPositionY(sf::RenderWindow& ventanaPrueba) const {

	for (Ball ball : world.getBalls()) {
		return (int)ball.getPosition().y;
	}
}

float WorldRenderer::getVelocityX(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getVelocity().x;
	}
}
float WorldRenderer::getVelocityY(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getVelocity().y;
	}
}
//cout << "X: " << ((int)(ball.getPosition().x / 60)) - 1 << " " << "Y: " << ((int)ball.getPosition().y / 60) - 1 << endl;

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


