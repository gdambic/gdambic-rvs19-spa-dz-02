#include "Start_Screen.h"
#include <iostream>

//Na Start Screenu mozda ubaciti stvari sastrane da ne izgleda monotono

Start_Screen::Start_Screen(sf::RenderWindow* Window)
{
	this->Window = Window;
	set_height();
	set_width();
}

sf::Text Start_Screen::set_Naslov()
{
	if (!Naslov_font.loadFromFile("From-Cartoon-Blocks.ttf"))
	{
		std::cout << "Greska prilikom ocitavanja fonta naslova" << std::endl;
	}
	Naslov.setFont(Naslov_font);
	Naslov.setCharacterSize(200);
	Naslov.setString("Game of Life");
	Naslov.setOutlineColor(sf::Color::Red);
	Naslov.setOutlineThickness(20);
	Naslov.setFillColor(sf::Color::Green);
	Naslov.setStyle(sf::Text::Style::Bold);
	Naslov.setPosition(width - width * 0.6, height - height * 0.98);
	return Naslov;
}

sf::Text Start_Screen::set_PodNaslov()
{
	if (!Podnaslov_font.loadFromFile("Bunny-Rabbits.ttf"))
	{
		std::cout << "Greska prilikom ocitavanja fonta podnaslova" << std::endl;
	}
	Podnaslov.setFont(Podnaslov_font);
	Podnaslov.setCharacterSize(100);
	Podnaslov.setString("Choose Level Type");
	Podnaslov.setFillColor(sf::Color::Blue);
	Podnaslov.setStyle(sf::Text::Style::Bold);
	Podnaslov.setPosition(Naslov.getPosition().x , Naslov.getPosition().y + height * 0.15);
	return Podnaslov;
}

sf::Text Start_Screen::set_Levels()
{
	if (!Levels_font.loadFromFile("Bunny-Rabbits.ttf"))
	{
		std::cout << "Greska prilikom ocitavanja fonta" << std::endl;
	}
	Levels.setFont(Levels_font);
	Levels.setCharacterSize(50);
	Levels.setString("1.Small group, but you have animations \n2.Big group, but you do not have animations");
	Levels.setLineSpacing(2);
	Levels.setFillColor(sf::Color::Red);
	Levels.setStyle(sf::Text::Style::Bold);
	Levels.setPosition(Podnaslov.getPosition().x, Podnaslov.getPosition().y + height * 0.1);
	return Levels;
}

float Start_Screen::set_height()
{
	height = Window->getSize().x;

	return height;
}

float Start_Screen::set_width()
{
	width = Window->getSize().y;
	return width;
}

void Start_Screen::Draw()
{
	Window->draw(set_Naslov());
	Window->draw(set_PodNaslov());
	Window->draw(set_Levels());
	
}
