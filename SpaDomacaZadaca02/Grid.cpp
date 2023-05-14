#include "Grid.h"

// private function
void Grid::drawLine(RectangleShape& line)
{
	window->draw(line);
}

// constructors
Grid::Grid(sf::RenderWindow* window)
{
	this->window = window; // input window je jednak èlanskom windowu

	// rows
	this->line = RectangleShape(Vector2f(1536, 1));
	line.setFillColor(Color::White);
	for (int i = 0; i <= 48; i++) {
		rows.push_back(line); 
		line.setPosition(0, i * 16);
	}

	// columns
	this->line = RectangleShape(Vector2f(1, 768));
	line.setFillColor(Color::White);
	for (int i = 0; i <= 96; i++) {
		columns.push_back(line);
		line.setPosition(i * 16, 0);
	}
}

// public functions
void Grid::drawGrid()
{
	// draw rows
	for (int i = 1; i <= 48; i++) {
		window->draw(rows[i]);
	}
	// draw columns
	for (int i = 1; i <= 96; i++) {
		window->draw(columns[i]);
	}
}
