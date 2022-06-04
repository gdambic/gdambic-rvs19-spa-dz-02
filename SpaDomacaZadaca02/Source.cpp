#include <SFML/Graphics.hpp>
#include "GameOfLife.h"
#include "Menu.h"

void start_the_game(char flag, static const unsigned int WIDTH, static const unsigned int HEIGHT);

int main()
{
	// screen resolution
	static const unsigned int WIDTH = 800;
	static const unsigned int HEIGHT = 600;

	sf::RenderWindow menu_window(sf::VideoMode(WIDTH, HEIGHT), "MAIN MENU");
	menu_window.setFramerateLimit(60);
	Menu menu(&menu_window, WIDTH, HEIGHT);

	while (menu_window.isOpen())
	{
		sf::Event event;
		while (menu_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				menu_window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					start_the_game('1', WIDTH, HEIGHT);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					start_the_game('2', WIDTH, HEIGHT);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					start_the_game('3', WIDTH, HEIGHT);
				}
				break;
			}

		}
		menu_window.clear();
		menu.draw();
		menu_window.display();
	}
	return 0;
}

void start_the_game(char flag, static const unsigned int WIDTH, static const unsigned int HEIGHT)
{
	//START THE GAME
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "THIS IS ALGEBRA GAME OF LIFE!");
	window.setFramerateLimit(60);
	GameOfLife game(&window, WIDTH, HEIGHT, flag);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
				{
					game.set_speed('+');
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
				{
					game.set_speed('-');
				}				
					break;
			}			
		}
		window.clear();
		game.draw();
		window.display();
	}
}
