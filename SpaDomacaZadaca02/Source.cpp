#include <SFML/Graphics.hpp>
#include<iostream>
#include"GameOL.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello, SFML world!");
	window.setFramerateLimit(60);
	GameOL GameOL(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		GameOL.draw();
		window.display();
	}

	return 0;
}