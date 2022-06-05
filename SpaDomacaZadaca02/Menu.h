#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
public:
	Menu(sf::RenderWindow* menu_window, int screen_width, int screen_height);
	void draw();
private:
	sf::RenderWindow* menu_window;
	int screen_width;
	int screen_height;
	sf::Texture key_num1;
	sf::Texture key_num2;
	sf::Texture key_num3;
	sf::Texture key_esc;
	sf::Font font;
};

