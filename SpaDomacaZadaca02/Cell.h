#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
class Cell
{
private:
	bool randomLife();
	sf::RenderWindow* window;
	sf::RectangleShape singleCell;
	vector<vector<sf::RectangleShape>> cells;
	int getNeighbor( int i, int j);
	void nextGen();
public:
	Cell(sf::RenderWindow* window);
	void draw();

};

