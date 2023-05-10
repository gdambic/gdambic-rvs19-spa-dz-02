#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"
#include "game_menu.h"

int VALUE_PACKER(int v, int vmax)
{
	if (v == -1) return vmax - 1;
	if (v == vmax) return 0;
	return v;
}

std::once_flag onceFlag;

int main()
{
	const int MAP_WIDTH = 80;
	const int MAP_HEIGHT = 80;
	const int CELL_SIZE = 10;
	const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
	const int N_CELLS = MAP_WIDTH * MAP_HEIGHT;
	int map[N_CELLS] = {};
	int mapNext[N_CELLS];
	int delay = 2;

	int rgb[3] = { 255,255,255 };
	int rgb_menu[3] = { 0,0,0 };
	srand(time(NULL));

	for (int i = 0; i < N_CELLS; i++)
		map[i] = (get_rnd(1, 4) == 1) ? 1 : 0;

	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT), "Game of life");
	window.setFramerateLimit(60);
	int current_menu_state = 0;
	int game_definition_index = 0;
	game_menu menu(window.getSize().x, window.getSize().y, "Start", "Postavke", "Modify Delay", "Izlaz", true);
	game_menu subcategory1(window.getSize().x, window.getSize().y, "Resample", "Randomise CELL RGB", "Randomise MENU font and RGB usage", "Custom Resample Chance", true);
	game_menu subcategory2(window.getSize().x, window.getSize().y, "5 second", "2 second", "1 second", "0 second", true);
	game_menu subcategory3(window.getSize().x, window.getSize().y, "50% chance of 1", "33% chance of 1", "25 % chance of 1", "10 % chance of 1", true);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (current_menu_state)
				{
				case 0:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.moveup();
						break;
					case sf::Keyboard::Down:
						menu.movedown();
						break;
					case sf::Keyboard::Enter:
						switch (menu.get_pressed_item())
						{
						case 0:
							std::cout << "Init. Game!" << std::endl;
							current_menu_state = 1;
							break;
						case 1:
							std::cout << "Subcategory 1!" << std::endl;
							current_menu_state = 2;
							break;
						case 2:
							std::cout << "Subcategory 2!" << std::endl;
							current_menu_state = 3;
							break;
						case 3:
							window.close();
							return 0;
							break;
						}
						break;
					}
					break;
				case 1:
					if (event.key.code == sf::Keyboard::Backspace)
					{
						window.clear(sf::Color::Black);
						std::cout << "Return!" << std::endl;
						current_menu_state = 0;
					}
					break;
				case 2:
					switch (event.key.code)
					{
					case sf::Keyboard::BackSpace:
						window.clear(sf::Color::Black);
						std::cout << "Return!" << std::endl;
						current_menu_state = 0;
						break;
					case sf::Keyboard::Up:
						subcategory1.moveup();
						break;
					case sf::Keyboard::Down:
						subcategory1.movedown();
						break;
					case sf::Keyboard::Enter:
						switch (subcategory1.get_pressed_item())
						{
						case 0:
							std::cout << "Resampled!" << std::endl;
							for (int i = 0; i < N_CELLS; i++)
								map[i] = (get_rnd(1, 4) == 1) ? 1 : 0;
							break;
						case 1:
							std::cout << "RGB Changed! " << std::endl;
							for (int i = 0; i < 3; i++)
								rgb[i] = get_rgb();
							std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
							break;
						case 2:
							std::cout << "Yes! I do as you say!" << std::endl;
							rgb_menu[0] = get_rgb();
							rgb_menu[1] = get_rgb();
							rgb_menu[2] = get_rgb();
							menu.randomise_font(window);
							subcategory1.randomise_font(window);
							subcategory2.randomise_font(window);
							break;
						case 3:
							current_menu_state = 4;
							std::cout << "Subcategory 3!" << std::endl;
							break;
						}
						break;
					}
					break;
				case 3:
					switch (event.key.code)
					{
					case sf::Keyboard::BackSpace:
						window.clear(sf::Color::Black);
						std::cout << "Return!" << std::endl;
						current_menu_state = 0;
						break;
					case sf::Keyboard::Up:
						subcategory2.moveup();
						break;
					case sf::Keyboard::Down:
						subcategory2.movedown();
						break;
					case sf::Keyboard::Enter:
						switch (subcategory2.get_pressed_item())
						{
						case 0:
							std::cout << "Delay changed!" << std::endl;
							delay = 5;
							current_menu_state = 0;
							break;
						case 1:
							std::cout << "Delay changed!" << std::endl;
							delay = 2;
							current_menu_state = 0;
							break;
						case 2:
							std::cout << "Delay changed!" << std::endl;
							delay = 1;
							current_menu_state = 0;
							break;
						case 3:
							delay = 0;
							std::cout << "Delay changed!" << std::endl;
							current_menu_state = 0;
							break;
						}
						break;
					}
					break;
				case 4:
					switch (event.key.code)
					{
					case sf::Keyboard::BackSpace:
						window.clear(sf::Color::Black);
						std::cout << "Return!" << std::endl;
						current_menu_state = 0;
						break;
					case sf::Keyboard::Up:
						subcategory3.moveup();
						break;
					case sf::Keyboard::Down:
						subcategory3.movedown();
						break;
					case sf::Keyboard::Enter:
						switch (subcategory3.get_pressed_item())
						{
						case 0:
							std::cout << "DONE! 50%" << std::endl;
							for (int i = 0; i < N_CELLS; i++)
								map[i] = (get_rnd(1, 2) == 1) ? 1 : 0;
							current_menu_state = 2;
							break;
						case 1:
							std::cout << "DONE! 33%" << std::endl;
							for (int i = 0; i < N_CELLS; i++)
								map[i] = (get_rnd(1, 3) == 1) ? 1 : 0;
							current_menu_state = 2;
							break;
						case 2:
							std::cout << "DONE! 25%" << std::endl;
							for (int i = 0; i < N_CELLS; i++)
								map[i] = (get_rnd(1, 4) == 1) ? 1 : 0;
							current_menu_state = 2;
							break;
						case 3:
							std::cout << "DONE! 10%" << std::endl;
							for (int i = 0; i < N_CELLS; i++)
								map[i] = (get_rnd(1, 10) == 1) ? 1 : 0;
							current_menu_state = 2;
							break;
						}
						break;
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		switch (current_menu_state)
		{
		case 0:
			window.clear(sf::Color(rgb_menu[0], rgb_menu[1], rgb_menu[2]));
			menu.draw(window);
			break;
		case 1:
			window.clear(sf::Color::Black);
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				for (int y = 0; y < MAP_HEIGHT; y++)
				{
					sf::RectangleShape cell;
					cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
					cell.setSize(CELL_VECTOR);
					cell.setOutlineThickness(1);
					cell.setOutlineColor(sf::Color::Black);
					if (map[x + y * MAP_WIDTH] == 1)
						cell.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
					else
						cell.setFillColor(sf::Color::Black);
					window.draw(cell);
					int nearby_cell_sum = 0;
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
						{
							int xi = VALUE_PACKER(x + i, MAP_WIDTH);
							int yj = VALUE_PACKER(y + j, MAP_HEIGHT);
							nearby_cell_sum += map[xi + yj * MAP_WIDTH];
						}
					int current = x + y * MAP_WIDTH;
					nearby_cell_sum -= map[current];
					mapNext[current] = map[current];
					if (map[current] == 1 && (nearby_cell_sum < 2 || nearby_cell_sum > 3))
						mapNext[current] = 0;
					else if (nearby_cell_sum == 3)
						mapNext[current] = 1;
				}
			}
			for (int i = 0; i < N_CELLS; i++)
				map[i] = mapNext[i];
			sf::sleep(sf::seconds(delay));
			break;
		case 2:
			window.clear(sf::Color(rgb_menu[0], rgb_menu[1], rgb_menu[2]));
			subcategory1.draw(window);
			break;
		case 3:
			window.clear(sf::Color(rgb_menu[0], rgb_menu[1], rgb_menu[2]));
			subcategory2.draw(window);
			break;
		case 4:
			window.clear(sf::Color(rgb_menu[0], rgb_menu[1], rgb_menu[2]));
			subcategory3.draw(window);
			break;
		}
		window.display();
	}
	return 0;
}