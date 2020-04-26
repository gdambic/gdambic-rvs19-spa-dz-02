#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Start_Screen.h"
#include "Huge_Screen.h"
#include "Small_Screen.h"
#include <Windows.h>

using namespace std;
using namespace std::chrono;

void provjera(sf::RenderWindow& window, sf::Event& event, bool& home, bool& izbor, Huge_Screen& huge_screen) 
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (home)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();

			}
			if (event.key.code == sf::Keyboard::Num1)
			{
				izbor = true;
				home = false;
			}
			else if (event.key.code == sf::Keyboard::Numpad1)
			{
				izbor = true;
				home = false;
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				izbor = false;
				home = false;
			}
			else if (event.key.code == sf::Keyboard::Numpad2)
			{
				izbor = false;
				home = false;
			}
		}
		if (izbor == true)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				home = true;

			}
		}
	}
}

int main()
{
	//Ako ne radi probati iskljuciti settings iz inicijalizacije Windowa i prva dva reda ukloniti
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;
	sf::VideoMode Rezolucija = sf::VideoMode::getFullscreenModes()[0];
	sf::RenderWindow window(Rezolucija, "Game Of Life", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(60);
	bool home = true;
	bool izbor;
	bool firstime = true;
	time_point<high_resolution_clock> Start;
	Start_Screen start_screen(&window);
	Huge_Screen huge_screen(&window);

	Small_Screen small_screen(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			provjera(window, event, home, izbor, huge_screen);
		}
		if (home)
		{
			window.clear(sf::Color(255,255,255));
			start_screen.Draw();
		}
		else
		{
			if (izbor)
			{
				window.clear(sf::Color::White);
				small_screen.draw();
				Sleep(2000);

			}
			else
			{
				Start = high_resolution_clock::now();
				window.clear(sf::Color(255,255,255));
				huge_screen.Draw();
				firstime = false;
				

			}
		}
		window.display();
		if (!home && !izbor)
		{
			while (true)
			{
				window.pollEvent(event);
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						home = true;
					}
				}
				auto End = high_resolution_clock::now();
				if (duration_cast<seconds>(End - Start).count() >= 2)
				{
					break;
				}
			}
		}
	}

	return 0;
}