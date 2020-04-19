#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
class Cell
{
public:
	Cell();

	void Draw( sf::RenderWindow& window);
	sf::Vector2i GetPos();
private:
	sf::RectangleShape m_Shape;

	int size = 100;
	sf::Vector2f m_Position;
	
};

