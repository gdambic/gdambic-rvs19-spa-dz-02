#include "Game.h"

Game::Game(Cell** theCells)
{
	this->theCells = theCells;
}

int Game::getNeighbours(unsigned int y, unsigned int x)
{
	int counter = 0;
	if (!(x == 0 || y == 0))
	{
		counter += (theCellsCopy[y - 1][x - 1].alive == 1);
	}
	if (!(x == 0))
	{
		counter += (theCellsCopy[y][x - 1].alive == 1);
	}
	if (!(x == 0 || y == MaxY - 1))
	{
		counter += (theCellsCopy[y + 1][x - 1].alive == 1);
	}
	if (!(y == 0))
	{
		counter += (theCellsCopy[y - 1][x].alive == 1);
	}
	if (!(y == MaxY - 1))
	{
		counter += (theCellsCopy[y + 1][x].alive == 1);
	}

	if (!(x == MaxX - 1 || y == 0))
	{
		counter += (theCellsCopy[y - 1][x + 1].alive == 1);
	}
	if (!(x == MaxX - 1))
	{
		counter += (theCellsCopy[y][x + 1].alive == 1);
	}
	if (!(x == MaxX - 1 || y == MaxY - 1))
	{
		counter += (theCellsCopy[y + 1][x + 1].alive == 1);
	}

	return counter;
}

void Game::DeadOrAlive(unsigned int MaxX, unsigned int MaxY)
{
	this->MaxX = MaxX;
	this->MaxY = MaxY;

	theCellsCopy = new Cell * [MaxY];
	for (unsigned int i = 0; i < MaxY; i++)
	{
		theCellsCopy[i] = new Cell[MaxX];
	}

	for (unsigned int i = 0; i < MaxY; i++)
	{
		for (unsigned int j = 0; j < MaxX; j++)
		{
			theCellsCopy[i][j].alive = theCells[i][j].alive;
		}
	}

	for (unsigned int i = 0; i < MaxY; i++)
	{
		for (unsigned int j = 0; j < MaxX; j++)
		{
			if (theCellsCopy[i][j].alive == 1 && (getNeighbours(i, j) < 2 || getNeighbours(i, j) > 3))
			{
				theCells[i][j].alive = 0;
			}
			if (theCellsCopy[i][j].alive == 0 && getNeighbours(i, j) == 3)
			{
				theCells[i][j].alive = 1;
			}
		}
	}

	for (int i = 0; i < MaxY; i++)
	{
		delete[] theCellsCopy[i];
	}
	delete[] theCellsCopy;
}

void Game::loadRender(sf::RenderWindow* window)
{
	this->window = window;
}

void Game::render()
{


	for (int i = 0; i < MaxY; i++)
	{
		for (int j = 0; j < MaxX; j++)
		{
			theCells[i][j].render(i, j, window);
		}
	}
}
