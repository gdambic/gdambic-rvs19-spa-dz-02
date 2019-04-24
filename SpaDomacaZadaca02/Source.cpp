#include <SFML/Graphics.hpp>
#include "IgraZivota.h"

int main()
{
	bool prvi = true;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello, SFML world!");
	window.setFramerateLimit(60);
	IgraZivota igra(&window);
	Clock sat;
	igra.draw(sat);
	window.display();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sat.getElapsedTime() >= seconds(2)) {
			window.clear();
			igra.simulacija();
			window.display();
			sat.restart();
		}
	}

	return 0;
}