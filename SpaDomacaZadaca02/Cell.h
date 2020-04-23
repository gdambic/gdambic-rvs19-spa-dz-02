#pragma once
#include <SFML/Graphics.hpp>
class Cell
{
public:
	bool alive;
	Cell(bool alive);
	Cell();
	void render(unsigned int y, unsigned int x, sf::RenderWindow* window);
};

