#include "Grid.h"
#include <iostream>
using namespace std;
Grid::Grid()
{
	m_RectangleShape.setSize(sf::Vector2f(size, size));
	m_RectangleShape.setFillColor(sf::Color(255, 255, 255));
}

Grid::~Grid()
{
}

void Grid::addPopulation(const sf::Vector2i& pos)
{
	if (pos.x >= 0 && pos.x < width * size && pos.y >= 0 && pos.y < height * size)
	{
		//cout << "Dodana populacija: " << endl;
		population[pos.x / size][pos.y / size] = true;
	}
	
}

void Grid::drawAllCells(sf::RenderWindow &window)
{ 
	sf::Texture m_RectangleShapeTexture;
	m_RectangleShapeTexture.loadFromFile("Texture/pacman-png-24.png");
	m_RectangleShape.setTexture(&m_RectangleShapeTexture);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (population[i][j] == true)
			{
				//cout << "Nacrtaj populaciju" << endl;
				m_RectangleShape.setPosition(sf::Vector2f(i  *size, j  * size));
				window.draw(m_RectangleShape);
			}
		}
	}
}

void Grid::update(float deltaTime)
{
	m_refreshTimer += deltaTime;
	if (m_refreshTimer >= m_refreshRate)
	{
		m_refreshTimer = 0.0f;
		bool tickPopulation[500][400];


		//cout << "Update: " << endl;
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				int count = countNeighbours(i, j);

				if (population[i][j] == true)
				{
					if (count <= 1)
					{//umri
						tickPopulation[i][j] = false;
					}

					else if (count >= 2 && count <= 3)
					{
						//zivi do sljedece generacije
								//cout << "ostani ziv" << endl;
						tickPopulation[i][j] = true;
					}


					else if (count > 3)
					{
						tickPopulation[i][j] = false;
					}
						
				}
					else if (count == 3)
				{//stvori novu generaciju
					tickPopulation[i][j] = true;
				}
						





				
			}
		}
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				population[i][j] = false;
				population[i][j] = tickPopulation[i][j];
			}
		}

	}
}


int Grid::countNeighbours(int x, int y)
{
	int count = 0;
	
	if (population[x-1][y-1] == true)
	{
		++count;
	}
	if (population[x][y-1] == true)
	{
		++count;
	}
	if (population[x + 1][y-1] == true)
	{
		++count;
	}
	if (population[x - 1][y] == true)
	{
		++count;
	}
	if (population[x + 1][y] == true)
	{
		++count;
	}
	if (population[x - 1][y+1] == true)
	{
		++count;
	}
	if (population[x ][y + 1] == true)
	{
		++count;
	}
	if (population[x + 1][y + 1] == true)
	{
		++count;
	}
	return count;
}


