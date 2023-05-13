#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
class Grid
{
private:
	sf::RenderWindow* window;
	sf::RectangleShape r;
	vector<sf::RectangleShape> rows ;
	vector<sf::RectangleShape> cols ;
	void drawRectangle(sf::RectangleShape& r);
	
public:
	Grid(sf::RenderWindow* window);
	void draw();
};

