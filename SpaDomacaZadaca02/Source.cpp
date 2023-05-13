#include <SFML/Graphics.hpp>
#include <windows.h>
#include "draw_gol.h"
#include <iostream>
using namespace std;

// Master_Of_Puppets.wav



int main()
{

	std::string cwd;
	char buffer[MAX_PATH];
	if (GetCurrentDirectoryA(MAX_PATH, buffer) != 0) {
		cwd = buffer;
		std::cout << "Current working directory: " << cwd << std::endl;
	}
	else {
		std::cerr << "Failed to get the current working directory" << std::endl;
	}

	cwd += "/Music/Master_Of_Puppets.wav";
	std::wstring musicPath(cwd.begin(), cwd.end());
	//PlaySound(musicPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of life");
	window.setFramerateLimit(60);
	draw_gol d(&window);
	
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					d.mouse_clicked_left(mousePosition);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					d.mouse_clicked_right(mousePosition);
				}
				
			}

		}
		window.clear();
		d.watch_gol();
		if (d.need_generation_count() < 100)
		{
			Sleep(100);
		}
		else if (d.need_generation_count() < 500)
		{
			Sleep(50);
		}
		else if (d.need_generation_count() < 1000)
		{
			Sleep(10);
		}
		
		window.display();

	}
	
	
	
	return 0;
}