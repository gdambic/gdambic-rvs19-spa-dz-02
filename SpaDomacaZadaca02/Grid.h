#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Grid
{
private:
	// variables
	RenderWindow* window;
	RectangleShape line;
	vector <RectangleShape> rows;
	vector <RectangleShape> columns;

	// private function
	void drawLine(RectangleShape& rectangle);

public:
	// constructors
	Grid (RenderWindow* window);

	// public functions
	void drawGrid();
};

