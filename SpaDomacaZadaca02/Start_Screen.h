#pragma once
#include "SFML/Graphics.hpp"
class Start_Screen
{
public:
	Start_Screen(sf::RenderWindow* Window);
	sf::Text set_Naslov();
	sf::Text set_PodNaslov();
	sf::Text set_Levels();
	float set_height();
	float set_width();
	void Draw();

private:

	sf::RenderWindow* Window;
	sf::Text Naslov;
	sf::Font Naslov_font;
	sf::Text Podnaslov;
	sf::Font Podnaslov_font;
	sf::Text Levels;
	sf::Font Levels_font;
	float height;
	float width;
};
