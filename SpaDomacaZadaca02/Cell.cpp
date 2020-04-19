#include "Cell.h"




Cell::Cell() : m_Position{sf::Vector2f(100.0f,100.0f)}
{
	m_Shape.setSize(sf::Vector2f(size, size));
	m_Shape.setFillColor(sf::Color(255, 255, 255));
	m_Shape.setPosition(m_Position);
}



void Cell::Draw( sf::RenderWindow& window)
{
	 
	window.draw(m_Shape);
	
}


sf::Vector2i Cell::GetPos()
{
	return sf::Vector2i(std::round(m_Position.x), std::round(m_Position.y));
}