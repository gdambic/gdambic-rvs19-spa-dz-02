#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
using namespace std;




void Grid::drawRectangle(sf::RectangleShape& r)
{
	window->draw(r);
}

Grid::Grid(sf::RenderWindow* window)
{
	
	this->r = sf::RectangleShape(sf::Vector2f(1, 600));
	r.setFillColor(sf::Color::Cyan);
	for (int i = 0; i <= 40; ++i) {
		cols.push_back(r);
		r.setPosition(i*20, 0);
	}
	this->r = sf::RectangleShape(sf::Vector2f(800, 1));
	r.setFillColor(sf::Color::Cyan);
	for (int i = 0; i <= 20; ++i) {
		rows.push_back(r);
		r.setPosition(0, i * 30);
	}

	
	this->window = window;
}

void Grid::draw()
{
	
	for (int i = 0; i <= 40; ++i) {
		window->draw(cols[i]);
	}
	for (int i = 0; i <= 20; ++i) {
		window->draw(rows[i]);
	}
	
}
