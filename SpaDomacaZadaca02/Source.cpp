#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>

#include "TheWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "1-Player Conway's Game of Life");
	window.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	//view.setViewport(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	window.setView(view);

	std::cout << "Welcome to Conway's Game of Life." << std::endl;
	std::cout << "You can move using your mouse's ScrollWheel, and by holding Crtl or Shift and using the ScrollWheel." << std::endl;
	std::cout << "You can place dots by LeftClicking or remove them by RightClicking." << std::endl;
	std::cout << "You can use Left and Right arrows to control processing time. Space is used to pause the simulation." << std::endl;
	std::cout << "Up and Down arrows control how many chunks regeneration will create. You can trigger it by pressing BackSpace." << std::endl;
	std::cout << "You can press R to reset your view." << std::endl;
	std::cout << "Hitting Enter will display chunk data." << std::endl;
	std::cout << "Escape ends the program." << std::endl;

	TheWorld world;
	bool simulating = true;
	int key_cooldown = 0;
	int standard_key_cooldown = 10;

	int simulation_counter = 0;
	int simulation_time = 120;

	float default_view_center_x = world.get_world_default_position() + 50;
	float default_view_center_y = world.get_world_default_position() + 50;
	float offset_x = 0;
	float offset_y = 0;
	//float zoom = 1;
	double zoom = 0.5;

	while (window.isOpen())
	{
		simulation_counter++;//TODO: make time-dependant, not frame dependant
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
				world.set_dot(std::floor(worldPos.x), std::floor(worldPos.y), true);

				std::cout << "(Experimental) LMB pressed at " << worldPos.x << ", " << worldPos.y << "." << std::endl;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
				world.set_dot(std::floor(worldPos.x), std::floor(worldPos.y), false);

				std::cout << "(Experimental) RMB pressed at " << worldPos.x << ", " << worldPos.y << "." << std::endl;
			}

			//Keys with cooldown ahead
			if (!(key_cooldown > 0)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "ESC pressed. Exiting..." << std::endl;
					exit(0);
				}

				//Build order
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
					key_cooldown = standard_key_cooldown;
					world.increment_rebuild_chunk_number();
					std::cout << "UP pressed. Number of starting chunks is " << world.get_rebuild_chunk_number() << '.' << std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
					key_cooldown = standard_key_cooldown;
					world.decrement_rebuild_chunk_number();
					std::cout << "DOWN pressed. Number of starting chunks is " << world.get_rebuild_chunk_number() << '.' << std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "BACKSPACE pressed. Rebuilding." << std::endl;
					world.rebuild();
				}

				//Time control
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
					key_cooldown = standard_key_cooldown;
					simulation_time += 10;
					std::cout << "RIGHT pressed. Sim time is " << simulation_time << " frames." << std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
					key_cooldown = standard_key_cooldown;
					if (simulation_time > 0)
						simulation_time -= 10;
					std::cout << "LEFT pressed. Sim time is " << simulation_time << " frames." << std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					key_cooldown = standard_key_cooldown;
					simulating = !simulating;
					std::cout << "SPACE pressed. Pause toggled." << std::endl;
				}

				//View reset
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "R pressed. Resetting view." << std::endl;
					offset_x = 0;
					offset_y = 0;
					zoom = 1;
				}

				//Chunk control
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					key_cooldown = standard_key_cooldown;
					std::cout << "ENTER pressed. Toggling chunk visibility." << std::endl;
					world.toggle_show_chunks();
				}
			}//End of keys with cooldown

			if (event.type == sf::Event::MouseWheelScrolled) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
					if (event.mouseWheelScroll.delta > 0) {
						offset_x += 50 * zoom;
					}
					else {
						offset_x -= 50 * zoom;
					}
					continue;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
					if (event.mouseWheelScroll.delta > 0) {
						offset_y -= 50 * zoom;
					}
					else {
						offset_y += 50 * zoom;
					}
					continue;
				}

				float last_zoom = zoom;
				if (event.mouseWheelScroll.delta > 0) {
					if (zoom <= 0.15) {//too close
						continue;
					}
					zoom -= 0.10;
				}
				else {
					zoom += 0.10;
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

		world.draw(window, zoom);

		window.display();
	}

	return 0;
}