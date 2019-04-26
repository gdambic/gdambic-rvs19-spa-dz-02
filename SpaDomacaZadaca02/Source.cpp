#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <vector>

void tutorial(sf::RenderWindow* window, float VRIJEME) {
	sf::Font font;
	font.loadFromFile("consola.ttf");
	sf::Text text("strelice/WASD - povecaj/smanji stupce/retke | 1/2 - povecaj/smanji kvadratice | R - reset | Q - korak | C - ocisti\n+/- - ubrzaj/uspori | lijevi klik - promjeni celiju | SPACE - zaustavi | frekvencija: " + to_string(VRIJEME==0 ? 0 : 1/VRIJEME) + " Hz", font);
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
			
			switch (event.type)
			{
			case sf::Event::MouseMoved:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					game_of_life.klik(position.x, position.y);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					game_of_life.klik(position.x, position.y);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game_of_life.odklik();
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					AUTOPLAY = AUTOPLAY ? false : true;

				}
				else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W) {

					game_of_life.REDAKAdown();
				}
				else if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S) {

					game_of_life.REDAKAup();
				}
				else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {

					game_of_life.STUPACAup();
				}
				else if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {

					game_of_life.STUPACAdown();
				}
				else if (event.key.code == sf::Keyboard::Numpad1 or event.key.code == sf::Keyboard::Num1) {

					game_of_life.SIZEup();
				}
				else if (event.key.code == sf::Keyboard::Numpad2 or event.key.code == sf::Keyboard::Num2) {

					game_of_life.SIZEdown();
				}
				else if (event.key.code == sf::Keyboard::R) {

					game_of_life.reset();
				}
				else if (event.key.code == sf::Keyboard::Q) {

					game_of_life.sljedeca_generacija();
				}
				else if (event.key.code == sf::Keyboard::C) {

					game_of_life.ocisti();
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
				else if (event.key.code == sf::Keyboard::Space) {
					AUTOPLAY= !AUTOPLAY;
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		if (clock.getElapsedTime().asSeconds() > VRIJEME && AUTOPLAY) {
			clock.restart();
			game_of_life.sljedeca_generacija();
			
		}
		window.clear();
		game_of_life.iscrtaj();
		tutorial(&window, AUTOPLAY ? VRIJEME : 0.0);
		window.display();
	}

	return 0;
}