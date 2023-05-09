#pragma once
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

class Background
{
private:
	sf::RenderWindow* window;
	sf::Color color;
	sf::RectangleShape bg;
	list<sf::Color> colors;
public:
	Background(sf::RenderWindow* window);
	void changeColor();
	void draw();

};

