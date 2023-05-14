#include "draw_gol.h"

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

	std::string music_path = cwd + "/Music/Master_Of_Puppets.wav";
	std::wstring musicPath(music_path.begin(), music_path.end());
	//PlaySound(musicPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of life");
	window.setFramerateLimit(60);
	draw_gol d(&window, cwd);
	
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

		d.watch_gol();

		if (d.need_generation_count() >= 20 && d.need_generation_count() <= 40)
		{
			d.cat_falling();
		}
		if (d.need_generation_count() >= 45 && d.need_generation_count() <= 55)
		{
			d.scratching();
		}
		if (d.need_generation_count() >= 60 && d.need_generation_count() <= 90)
		{
			d.curious_streach();
		}
		if (d.need_generation_count() >= 90 && d.need_generation_count() <= 110)
		{
			d.boom();
		}
		if (d.need_generation_count() == 111)
		{
			sf::Vector2u windowSize = window.getSize();

			// Calculate the center coordinates
			float centerX = windowSize.x / 2.0f;
			float centerY = windowSize.y / 2.0f;
			std::cout << "Center X: " << centerX << std::endl;
			std::cout << "Center Y: " << centerY << std::endl;
			d.call_big_boom(centerX, centerY);
		}
		
		window.display();

	}
	
	
	
	return 0;
}