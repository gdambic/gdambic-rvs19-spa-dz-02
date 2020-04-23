#pragma once
#include "Cell.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(Cell** theCells);
	void DeadOrAlive(unsigned int MaxX, unsigned int MaxY);
	void loadRender(sf::RenderWindow* window);
	void render();
private:
	Cell** theCells;
	Cell** theCellsCopy;
	unsigned int MaxX;
	unsigned int MaxY;
	sf::RenderWindow* window;
	int getNeighbours(unsigned int x, unsigned int y);
};

