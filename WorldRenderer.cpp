#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World& world) : world(world) {}

WorldRenderer::~WorldRenderer() {}

//Carga el mundo
void WorldRenderer::render(sf::RenderWindow& ventanaPrueba) const {
	renderBalls(ventanaPrueba);
}

//Carga en pantalla el balon
void WorldRenderer::renderBalls(sf::RenderWindow& ventanaPrueba) const {
	for (Ball ball : world.getBalls()) {
		ball.draw(ventanaPrueba);
	}

}

//Devuelve la posicion en X
int WorldRenderer::getPositionX(sf::RenderWindow& ventanaPrueba) const{

	for (Ball ball : world.getBalls()) {
		return (int)ball.getPosition().x;
	}
}

//Devuelve la posicion en Y
int WorldRenderer::getPositionY(sf::RenderWindow& ventanaPrueba) const {

	for (Ball ball : world.getBalls()) {
		return (int)ball.getPosition().y;
	}
}

//Devuelve la velocidad del balon en X
float WorldRenderer::getVelocityX(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getVelocity().x;
	}
}

//Devuelve la velocidad del balon en Y
float WorldRenderer::getVelocityY(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getVelocity().y;
	}
}

//Se asigna la velocidad del balon
void WorldRenderer::setVelocity(sf::RenderWindow& ventanaPrueba, float x, float y) const
{
	for (Ball ball : world.getBalls()) {
		ball.setVelocity(x, y);
	}
}

//Devuelve el radio del balon
float WorldRenderer::getRadius(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getRadius();
	}
}

//se asigna la posicion del balon
void WorldRenderer::setPosition(sf::RenderWindow& ventanaPrueba, int x, int y) const
{
	for (Ball ball : world.getBalls()) {
		ball.setPosition(x, y);
	}
}

//Regresa los bordes del balon 
sf::FloatRect WorldRenderer::getGlobalBounds(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getBounds();
	}
}

//cout << "X: " << ((int)(ball.getPosition().x / 60)) - 1 << " " << "Y: " << ((int)ball.getPosition().y / 60) - 1 << endl;

//Devuelve el lado donde se metio gol
int WorldRenderer::getLado(sf::RenderWindow& ventanaPrueba) const
{
	for (Ball ball : world.getBalls()) {
		return ball.getLado();
	}
}

//Se asigna el lado donde se mete gol
void WorldRenderer::setLado(sf::RenderWindow& ventanaPrueba)
{
	for (Ball ball : world.getBalls()) {
		ball.setLado(0);
	}
}


