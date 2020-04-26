#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Huge_Screen
{
public:
	Huge_Screen(sf::RenderWindow* Window);
	void set_Cells();
	sf::RectangleShape set_Cell();
	sf::Vector2f set_position();
	sf::Vector2f set_size();
	sf::Vector2f set_text_position();
	sf::Text set_prev_gen();
	sf::Font set_Font_prev_gen();
	sf::Text set_this_gen();
	sf::Font set_Font_this_gen();
	sf::Text set_High_Scor();
	sf::Font set_Font_High_Scor();
	float set_height();
	float set_width();
	void set_ss(int number);
	void Draw();

private:
	
	sf::RenderWindow* Window;
	sf::RectangleShape Cell;
	sf::Vector2f size;
	sf::Vector2f Cell_position;
	sf::Vector2f Text_position;
	sf::Text Prev_Gen;
	sf::Font Font_Prev_Gen;
	sf::Text This_Gen;
	sf::Font Font_This_Gen;
	sf::Text High_Scor;
	sf::Font Font_High_Scor;
	bool Cells[50][50];
	bool PrevCells[50][50];
	bool firstTime;
	float size1;
	float height;
	float width;
	int died = 0;
	int live = 0;
	int born = 0;
	stringstream ss_This_Gen;
	stringstream ss_Prev_Gen;
	stringstream ss_High_Scor;
	int Counter;
	int high;
	int high_live;
	int high_died;
	int high_born;
};

