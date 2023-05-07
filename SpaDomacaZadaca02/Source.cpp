#include <SFML/Graphics.hpp>
#include <iostream>

#include "TheWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "1P Conway's Game of Life");
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
	int key_cooldown = 0;
	int standard_key_cooldown = 5;

	int simulation_counter = 0;
	int simulation_time = 120;

	std::cout << "Welcome to Conway's Game of Life." << std::endl;
	std::cout << "You can move using your mouse's scrollwheel, and you can place dots by left clicking or remove them by right clicking." << std::endl;
	std::cout << "You can use ESC to pause, LR arrows to control time, UD arrows and SPACE to regenerate the tiles, ENTER to show chunk data." << std::endl;

	while (window.isOpen())
	{
		simulation_counter++;
		if (simulation_counter > simulation_time) {
			simulation_counter = 0;
			if(simulating)
				world.do_tick();
		}

		if (key_cooldown > 0) {
			key_cooldown--;
		}

		//world.set_dot(key_cooldown, key_cooldown, true);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
				world.set_dot(worldPos.x, worldPos.y, true);

				std::cout << "(Experimental) LMB pressed at " << worldPos.x << ", " << worldPos.y << "." << std::endl;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
				world.set_dot(worldPos.x, worldPos.y, false);

				std::cout << "(Experimental) RMB pressed at " << worldPos.x << ", " << worldPos.y << "." << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "ESC pressed." << std::endl;
					simulating = !simulating;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					world.chunks_to_start_with++;
					std::cout << "UP pressed. Number of starting chunks is " << world.chunks_to_start_with << '.' << std::endl;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					world.chunks_to_start_with--;
					std::cout << "DOWN pressed. Number of starting chunks is " << world.chunks_to_start_with << '.' << std::endl;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "SPACE pressed. Rebuilding." << std::endl;
					world.rebuild();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					simulation_time += 10;
					std::cout << "RIGHT pressed. Sim time is " << simulation_time << '.' << std::endl;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					if (simulation_time > 0)
						simulation_time -= 10;
					std::cout << "LEFT pressed. Sim time is " << simulation_time << '.' << std::endl;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
				if (!(key_cooldown > 0)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "ENTER pressed. Toggling chunk visibility." << std::endl;
					world.toggle_show_chunks();
				}
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
		view.setCenter(default_view_center_x + offset_x, default_view_center_y + offset_y);
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