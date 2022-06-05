#pragma once
#include <SFML/Graphics.hpp>
class GameOL
{
public:
	GameOL(sf::RenderWindow* window);
	void draw();
private:
	void setTime();
	void text();
	void pickColor();
	void change();
	void drawBoard();
	sf::RenderWindow* window;
	sf::Clock frameClock;
	int color[40][40];
	bool passed = true;
	sf::Time stop = sf::seconds(1.00f);

};

