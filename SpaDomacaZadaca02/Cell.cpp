#include "Cell.h"
#include <SFML/Graphics.hpp>

Cell::Cell(bool alive)
{
	this->alive = alive;
}

Cell::Cell()
{
	alive = 0;
}

void Cell::render(unsigned int y, unsigned int x, sf::RenderWindow* window)
{
	sf::RectangleShape cell(sf::Vector2f(10, 10));
	cell.setPosition(1 + 11 * x, 1 + 11 * y);
	if (alive)
	{
		cell.setFillColor(sf::Color(141, 252, 252));
	}
	else
	{
		cell.setFillColor(sf::Color(46, 46, 46));
	}
	window->draw(cell);
}
