#include <SFML/Graphics.hpp>
#include<iostream>

#include"Grid.h"

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Conways Game of Life! by Lovrhino Behnino");
	window.setFramerateLimit(144);
	
	window.setVerticalSyncEnabled(true);
	double deltaTime = 0.0f;
	bool updateGrid = false;
	Grid gridSystem;

	
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime += clock.getElapsedTime().asSeconds();
		
		clock.restart();
		
		cout <<deltaTime << endl;
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setSize(sf::Vector2u(event.size.width, event.size.height));
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
				{
					updateGrid = !updateGrid;
				}
				break;
			}
			

		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//stavi poziciju za populaciju
			gridSystem.addPopulation(sf::Mouse::getPosition(window));
			//cout << sf::Mouse::getPosition(window).x <<" : " << sf::Mouse::getPosition(window).y << endl;
		}

		if (updateGrid)
		{
			//cout << "Update: " << endl;
			gridSystem.update(deltaTime);
		}

		window.clear(sf::Color::Black);
		
		
		
		gridSystem.drawAllCells(window);
		window.display();
		clock.restart();
	}

	return 0;
}  