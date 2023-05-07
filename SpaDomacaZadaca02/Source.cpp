#include <SFML/Graphics.hpp>
#include <iostream>

#include "TheWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello, life!");
	window.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	//view.setViewport(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	window.setView(view);

	sf::CircleShape circle;
	circle.setRadius(5);

	float default_view_center_x = view.getCenter().x;
	float default_view_center_y = view.getCenter().y;
	float offset_x = 0;
	float offset_y = 0;
	float zoom = 1;

	TheWorld world;
	bool simulating = true;
	bool curr_press = false;
	int REMOVEME = 0;

	while (window.isOpen())
	{
		REMOVEME++;
		if (REMOVEME > 0) {//default 120
			REMOVEME = 0;
			if(simulating)
				world.do_tick();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
				curr_press = !curr_press;
				if (curr_press)
					continue;
				std::cout << "ESC pressed." << std::endl;
				simulating = !simulating;
			}


			if (event.type == sf::Event::MouseWheelScrolled) {
				float last_zoom = zoom;
				if (event.mouseWheelScroll.delta > 0) {
					if (zoom <= 0.05) {//too close
						break;
					}
					zoom -= 0.05;
				}
				else {
					zoom += 0.05;
				}

				//compiler will optimize (probably), very ugly
				/*
				Determines the mouse's position on the screen, determines how much the zoom will zoom in, sets the zoom as maximum movement,
				determines how far (%) the mouse is on the screen from the screen's center, and then multiplies the % with the maximum movement,
				letting the user move around with the scrollwheel.
				One of my favourite features in CAD programs tbh.
				*/
				float maximum_x = window.getSize().x * last_zoom - window.getSize().x * zoom;
				float maximum_y = window.getSize().x * last_zoom - window.getSize().x * zoom;

				float mouse_x = sf::Mouse::getPosition().x;
				float mouse_y = sf::Mouse::getPosition().y;

				//The values in these will be less than 50%. That's fine since maximums need to be divided by two anyhow so it doesn't overshoot
				float mouse_percent_x = (mouse_x - window.getPosition().x - 0.5 * window.getSize().x) / window.getSize().x;
				float mouse_percent_y = (mouse_y - window.getPosition().y - 0.5 * window.getSize().y) / window.getSize().y;

				offset_x += maximum_x * mouse_percent_x;//based on mouse position
				offset_y += maximum_y * mouse_percent_y;
			}
		}

		window.clear();

		view.setSize(window.getSize().x, window.getSize().y);
		view.zoom(zoom);
		view.setCenter(default_view_center_x + offset_x,
			default_view_center_y + offset_y);
		window.setView(view);

		/*circle.setPosition(50, 50);
		window.draw(circle);
		circle.setPosition(150, 150);
		window.draw(circle);*/

		world.draw(window);

		window.display();
	}

	return 0;
}