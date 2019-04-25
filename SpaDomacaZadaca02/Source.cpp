#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <vector>

void tutorial(sf::RenderWindow* window, float VRIJEME) {
	sf::Font font;
	font.loadFromFile("consola.ttf");
	sf::Text text("1/2 - povecaj/smanji stupce | 3/4 - povecaj/smanji retke | 5/6 - povecaj/smanji kvadratice\n+/- - ubrzaj/uspori | lijevi klik - promjeni celiju | frekvencija: " + to_string(1/VRIJEME) + " Hz", font);
	text.setCharacterSize(13);
	//text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	window->draw(text);
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game of life - by vanjavk");
	window.setFramerateLimit(60);
	game_of_life game_of_life(&window);
	sf::Clock clock;
	bool AUTOPLAY = true;
	float VRIJEME = 2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					AUTOPLAY = AUTOPLAY ? false : true;

				}
				else if (event.key.code == sf::Keyboard::Numpad5 or event.key.code == sf::Keyboard::Num5) {

					game_of_life.SIZEup();
				}
				else if (event.key.code == sf::Keyboard::Numpad6 or event.key.code == sf::Keyboard::Num6) {

					game_of_life.SIZEdown();
				}
				else if (event.key.code == sf::Keyboard::Add) {
					VRIJEME -= 0.1;
					if (VRIJEME < 0.1) {
						VRIJEME = 0.1;
					}
				}
				else if (event.key.code == sf::Keyboard::Subtract) {
					VRIJEME += 0.1;
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		cout << clock.getElapsedTime().asSeconds() << endl;
		if (clock.getElapsedTime().asSeconds() > VRIJEME) {
			clock.restart();
			game_of_life.sljedeca_generacija();
			
		}
		window.clear();
		game_of_life.iscrtaj();
		tutorial(&window, VRIJEME);
		window.display();
	}

	return 0;
}