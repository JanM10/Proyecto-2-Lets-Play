#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

int main(int argc, char *args[]) {

	bool flag = false;

	RenderWindow ventana(VideoMode(800, 600, 32), "Lets Play");

	while (!flag)
	{
		ventana.display();
	}

	return 0;
}