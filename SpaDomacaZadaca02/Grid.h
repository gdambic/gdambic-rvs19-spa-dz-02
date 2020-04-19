#pragma once
#include<SFML/Graphics.hpp>
class Grid
{
public:
	Grid();
	~Grid();
	void update(float deltaTime);
	void drawAllCells(sf::RenderWindow& window);
	void addPopulation(const sf::Vector2i& pos);
	int countNeighbours(int x, int y);
private:
	const int width{ 500 };
	const int height{ 400 };
	const int size = 10;
	bool population[500][400];

	sf::RectangleShape m_RectangleShape;
	float m_refreshRate = 0.01f;// brzina stanica
	float m_refreshTimer = 0.0f;
};

