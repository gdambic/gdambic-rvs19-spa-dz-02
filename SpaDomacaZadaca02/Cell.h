#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Cell{
private:
	// variables
	RenderWindow* window;
	RectangleShape singleCell;
	vector<vector<RectangleShape>> cells;

	// private functions
	int getNeighbor(int i, int j);
	void nextGeneration();
	bool randomLife();
public:
	// constructors
	Cell(RenderWindow* window);

	// public functions
	void drawCell();
};
