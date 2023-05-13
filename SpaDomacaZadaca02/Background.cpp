#include "Background.h"
#include <list>
#include <algorithm>
using namespace std;

Background::Background(sf::RenderWindow* window)
{
	this->window = window;
	this->color = sf::Color::Magenta;
	this->bg = sf::RectangleShape(sf::Vector2f(800, 600));
	this->bg.setFillColor(color);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Black);
}

void Background::changeColor()
{
	bg.setFillColor(colors.back());
	colors.push_front(colors.back());
	colors.pop_back();
}

void Background::draw()
{
	window->draw(bg);
}
