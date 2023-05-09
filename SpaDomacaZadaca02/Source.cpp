#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Cell.h"
#include "Background.h"
#include <iostream>
using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello, SFML world!");
	window.setFramerateLimit(2);
	cout << "Press 'c' to change colors! :D" << endl;
	Grid grid(&window);
	Cell cell(&window);
	Background bg(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				event.TextEntered == 'c';
				bg.changeColor();
			}
		}

		window.clear();
		bg.draw();
		cell.draw();
		grid.draw();
		window.display();
	}

	return 0;
}