#include "Cell.h"
#include "MyColors.h"

// private functions
int Cell::getNeighbor(int xIndex, int yIndex)
{
	int neighbour = 0;

	// rubni sluèajevi (uglovi)
	if (xIndex == 0 && yIndex == 0) {
		if (cells[xIndex + 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (xIndex == 0 && yIndex == 95) {
		if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (xIndex == 47 && yIndex == 95) {
		if (cells[xIndex - 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (xIndex == 47 && yIndex == 0) {
		if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	// rubni sluèajevi koji nisu uglovi
	else if (yIndex == 0) {
		if (cells[xIndex + 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (xIndex == 47) {
		if (cells[xIndex - 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (xIndex == 0) {
		if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex + 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	else if (yIndex == 95) {
		if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex + 1][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
			neighbour++;
		}
		if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
			neighbour++;
		}
		return neighbour;
	}

	// svi ostali sluèajevi
	if (cells[xIndex - 1][yIndex - 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex][yIndex - 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex + 1][yIndex - 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex + 1][yIndex].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex + 1][yIndex + 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex][yIndex + 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex - 1][yIndex + 1].getFillColor() == Lila) {
		neighbour++;
	}
	if (cells[xIndex - 1][yIndex].getFillColor() == Lila) {
		neighbour++;
	}
	return neighbour;
}

void Cell::nextGeneration()
{
	vector<vector<RectangleShape>> newGen(this->cells); // iz prošlog stanja gledam novo stanje
	for (int i = 0; i < 48; ++i) {
		for (int j = 0; j < 96; ++j) {
			if (this->cells[i][j].getFillColor() == Lila) {
				if (getNeighbor(i, j) < 2) {
					newGen[i][j].setFillColor(Color::Transparent);
				}
				else if (getNeighbor(i, j) == 2 || getNeighbor(i, j) == 3) {
					newGen[i][j].setFillColor(Lila);
				}
				else if (getNeighbor(i, j) > 3) {
					newGen[i][j].setFillColor(Color::Transparent);
				}
			}
			else if (this->cells[i][j].getFillColor() == Color::Transparent && getNeighbor(i, j) == 3) {
				newGen[i][j].setFillColor(Lila);
			}
		}
	}
	this->cells = newGen;
}

bool Cell::randomLife()
{
	return rand() % 4;;
}

// constructors
Cell::Cell(RenderWindow* window)
{
	srand(time(nullptr));
	this->window = window;
	this->singleCell = RectangleShape(Vector2f(14, 14));
	vector<RectangleShape> lineCells;

	for (int i = 0; i < 96; i++) {
		this->singleCell.setPosition(i * 16, 0);
		lineCells.push_back(this->singleCell);
	}

	for (int i = 0; i < 48; i++) {
		for_each(lineCells.begin(), lineCells.end(), [&i](RectangleShape& rectangle) {
			rectangle.setPosition(rectangle.getPosition().x, i * 16);
			});
		this->cells.push_back(lineCells);
	}

	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 96; j++) {
			if (randomLife() == 0) {
				this->cells[i][j].setFillColor(Lila);
			}
			else {
				this->cells[i][j].setFillColor(Color::Transparent);
			}
		}
	}
}

// public functions
void Cell::drawCell()
{
	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 96; j++) {
			window->draw(cells[i][j]);
		}
	}
	nextGeneration();
}
