#include <iostream>
#include "Input.h"
#include "Grid.h"
#include "Cell.h"
#include "MyColors.h"
#include <chrono>
using namespace std::chrono;

int main()
{
	Input widthHeight; // ne idu zagrade ovdje
	int width = widthHeight.getWidth();
	int height = widthHeight.getHeight();

	RenderWindow window(VideoMode(width, height), "Game of Life");
	window.setFramerateLimit(60);

	sf::Clock clock;
	Grid grid(&window); // adresu prozora šaljemo
	Cell cell(&window); // adresu prozora šaljemo

	while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Time dt = clock.restart();
		auto begin = high_resolution_clock::now();

		window.clear(Purple);
		cell.drawCell(); // moja funkcija
		grid.drawGrid(); // moja funkcija
		window.display();

		auto end = high_resolution_clock::now();
		cout << "Frame time: " << duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
	}

	return 0;
}