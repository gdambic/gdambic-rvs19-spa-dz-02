#include "Cell.h"
#include <iostream>
#include <ctime>
#include <algorithm>
bool Cell::randomLife()
{
	return rand() % 4;
}

int Cell::getNeighbor( int i, int j)
{
	int neighboor=0;
	if (i == 0 && j == 0) {
		if (cells[i + 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i + 1][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (i == 19 && j == 0) {
		if (cells[i-1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i - 1][j+1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (i == 19 && j == 39) {
		if (cells[i - 1][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i - 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (i == 0 && j == 39) {
		if (cells[i][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i + 1][j-1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i + 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (j == 0) {
		if (cells[i + 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i + 1][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i - 1][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i - 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (i == 19) {
		if (cells[i - 1][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i ][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i - 1][j+1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i - 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (i == 0) {
		if (cells[i][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i + 1][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i + 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i + 1][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i][j + 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}
	else if (j == 39) {
		if (cells[i - 1][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}if (cells[i+1][j - 1].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i + 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		if (cells[i - 1][j].getFillColor() == sf::Color::White) {
			++neighboor;
		}
		return neighboor;
	}

	if (cells[i - 1][j - 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i][j - 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i + 1][j - 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i + 1][j].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i + 1][j + 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i][j + 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i - 1][j + 1].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	if (cells[i - 1][j].getFillColor() == sf::Color::White) {
		++neighboor;
	}
	return neighboor;
}

void Cell::nextGen()
{
	vector<vector<sf::RectangleShape>> newGen(cells);
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 40; ++j) {
			if (cells[i][j].getFillColor() == sf::Color::White) {
				if (getNeighbor(i, j) < 2) {
					newGen[i][j].setFillColor(sf::Color::Transparent);
				}
				else if (getNeighbor(i, j) == 2 || getNeighbor(i, j) == 3) {

				}
				else if (getNeighbor(i, j) > 3) {
					newGen[i][j].setFillColor(sf::Color::Transparent);
				}
			}
			else if (cells[i][j].getFillColor() == sf::Color::Transparent && getNeighbor(i,j) == 3) {
				newGen[i][j].setFillColor(sf::Color::White);
			}
		}
	}
	cells = newGen;
}

Cell::Cell(sf::RenderWindow* window)
{
	srand(time(nullptr));
	this->singleCell = sf::RectangleShape(sf::Vector2f(20,30));
	vector<sf::RectangleShape> lineCells;
	for (int i = 0; i <40;++i) {
		singleCell.setPosition(i * 20, 0);
		lineCells.push_back(singleCell);
		
	}
	for (int i = 0; i < 20; ++i) {
		
		for_each(lineCells.begin(), lineCells.end(), [i](sf::RectangleShape& r) {
			r.setPosition(r.getPosition().x, i * 30);
			});
		cells.push_back(lineCells);
	}
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 40; ++j) {
			if (randomLife() == 0) {
				cells[i][j].setFillColor(sf::Color::White);
			}
			else {
				cells[i][j].setFillColor(sf::Color::Transparent);
			}
		}
	}
	this->window = window;

}

void Cell::draw()
{
	
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 40; ++j) {
			window->draw(cells[i][j]);
		}
	}
	nextGen();
	
}
