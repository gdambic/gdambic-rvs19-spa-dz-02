#include "Huge_Screen.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include <sstream>


Huge_Screen::Huge_Screen(sf::RenderWindow* Window)
{
	this->Window = Window;
	firstTime = true;
	Counter = 0;
	ifstream HighScor("High_Scor.txt");
	if (!HighScor)
	{
		cout << "Greska prilikom ucitavanja" << endl;
	}
	string temp;
	getline(HighScor, temp);
	getline(HighScor, temp, ':');
	getline(HighScor, temp, ' ');
	high_live = stoi(temp);
	getline(HighScor, temp);
	getline(HighScor, temp, ':');
	getline(HighScor, temp, ' ');
	high_born = stoi(temp);
	getline(HighScor, temp, ':');
	getline(HighScor, temp);
	high_died = stoi(temp);
	getline(HighScor, temp, ':');
	getline(HighScor, temp);
	high = stoi(temp);
	HighScor.close();
}

void Huge_Screen::set_Cells()
{
	died = 0;
	live = 0;
	born = 0;
	if (firstTime)
	{
		srand(time(nullptr));
		int broj;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				broj = rand() % 4 + 1;
				if (broj == 4)
				{
					Cells[i][j] = true;
					born++;
					live++;
				}
				else
				{
					Cells[i][j] = false;
				}
			}
		}
		set_ss(3);
	}

	else
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				PrevCells[i][j] = Cells[i][j];
			}
		}

		
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				int counter = 0;
				if (i - 1 >= 0 && j - 1 >= 0)
				{
					if (PrevCells[i-1][j-1])
					{
						counter++;
					}
				}
				if (j - 1 >=0)
				{
					if (PrevCells[j-1])
					{
						counter++;
					}
				}
				if (i + 1 < 50 && j - 1 >= 0)
				{
					if (PrevCells[i + 1][j - 1])
					{
						counter++;
					}
				}
				if (i + 1 < 50)
				{
					if (PrevCells[i + 1][j])
					{
						counter++;
					}
				}
				if (i + 1 < 50 && j + 1 <=50)
				{
					if (PrevCells[i + 1][j + 1])
					{
						counter++;
					}
				}
				if (j+1 < 50)
				{
					if (PrevCells[i][j +1])
					{
						counter++;
					}
				}
				if (i - 1 >= 0 && j + 1 < 50 )
				{
					if (PrevCells[i-1][j+1])
					{
						counter++;
					}
				}
				if (i -1 >= 0)
				{
					if (PrevCells[i - 1][j])
					{
						counter++;
					}
				}
				if (Cells[i][j])
				{
					if (counter > 3 || counter < 2)
					{
						Cells[i][j] = false;
						died++;
					}
					else
						live++;
				}
				else
				{
					if (counter == 3)
					{
						Cells[i][j] = true;
						born++;
						live++;
					}
				}
				counter = 0;
			}
		}
	}
	firstTime = false;
}

sf::RectangleShape Huge_Screen::set_Cell()
{
	Cell.setPosition(Cell_position);
	Cell.setSize(size);
	Cell_position.y += size.y*2;
	return Cell;
}

sf::Vector2f Huge_Screen::set_position()
{
	Cell_position.x = 0 + size.x;
	Cell_position.y = height * 0.2 + size.y;
	return Cell_position;
}

sf::Vector2f Huge_Screen::set_size()
{
	set_width();
	set_height();
	size.x = width / 100;
	size.y = height / 100;
	return size;
}

sf::Vector2f Huge_Screen::set_text_position()
{
	Text_position.x = width * 0.45;
	Text_position.y = height * 0.05;
	return Text_position;
}

sf::Text Huge_Screen::set_prev_gen()
{
	set_ss(1);
	set_Font_prev_gen();
	Prev_Gen.setFont(Font_Prev_Gen);
	Prev_Gen.setStyle(sf::Text::Style::Bold);
	Prev_Gen.setPosition(sf::Vector2f(width * 0.1, height * 0.05));
	Prev_Gen.setFillColor(sf::Color::Blue);
	Prev_Gen.setOutlineColor(sf::Color::Green);
	Prev_Gen.setOutlineThickness(5);
	Prev_Gen.setCharacterSize(20);
	Prev_Gen.setString(ss_Prev_Gen.str());
	return Prev_Gen;
}

sf::Font Huge_Screen::set_Font_prev_gen()
{
	if (!Font_Prev_Gen.loadFromFile("Asul-Regular.ttf"))
		std::cout << "Neuspjesno citanje fonta za this_gen podatke" << std::endl;

	return Font_Prev_Gen;
}

sf::Text Huge_Screen::set_this_gen()
{
	set_ss(2);
	set_Font_this_gen();
	This_Gen.setFont(Font_This_Gen);
	This_Gen.setCharacterSize(20);
	This_Gen.setStyle(sf::Text::Style::Bold);
	This_Gen.setPosition(set_text_position());
	This_Gen.setFillColor(sf::Color::Black);
	This_Gen.setOutlineColor(sf::Color::Red);
	This_Gen.setOutlineThickness(5);
	This_Gen.setString(ss_This_Gen.str());
	return This_Gen;
}

sf::Font Huge_Screen::set_Font_this_gen()
{
	if (!Font_This_Gen.loadFromFile("Asul-Regular.ttf"))
		std::cout << "Neuspjesno citanje fonta za this_gen podatke" << std::endl;
	
	return Font_This_Gen;
}

sf::Text Huge_Screen::set_High_Scor()
{
	if (Counter > high)
	{
		high = Counter;
		high_live = live;
		high_died = died;
		high_born = born;
	}
	set_ss(3);
	set_Font_High_Scor();
	High_Scor.setFont(Font_High_Scor);
	High_Scor.setCharacterSize(20);
	High_Scor.setStyle(sf::Text::Style::Bold);
	High_Scor.setPosition(sf::Vector2f(width * 0.8, height * 0.05));
	High_Scor.setFillColor(sf::Color::Blue);
	High_Scor.setOutlineColor(sf::Color::Red);
	High_Scor.setOutlineThickness(5);
	High_Scor.setLineSpacing(1);
	High_Scor.setString(ss_High_Scor.str());
	return High_Scor;
}

sf::Font Huge_Screen::set_Font_High_Scor()
{
	if (!Font_High_Scor.loadFromFile("Asul-Regular.ttf"))
		std::cout << "Neuspjesno citanje fonta za this_gen podatke" << std::endl;

	return Font_High_Scor;
}

float Huge_Screen::set_height()
{
	height = (Window->getSize().y) - (Window->getSize().y * 0.2);
	return height;
}

float Huge_Screen::set_width()
{
	width = Window->getSize().x - 20;
	return width;
}

void Huge_Screen::set_ss(int number)
{
	if (number == 1)
	{
		ss_This_Gen.str("");
		ss_Prev_Gen << "Prevolusion:" << endl
			<< "Live:" << live << "		"
			<< "Dead:" << 2500 - live << endl
			<< "Born:" << born << "	   "
			<< "Died:" << died << endl
			<< "	Live for:" << Counter << "sec" << endl;

		/*Stavit cu 3 izbora jedno this gen drugo prev gen i trece high scor
		brojanje pocinje na provjera funkciji pod num/pad 2*/
	}
	else if (number == 2)
	{
		ss_Prev_Gen.str("");
		ss_This_Gen << "Currently:" << endl
			<< "Live:" << live << "		"
			<< "Dead:" << 2500 - live << endl
			<< "Born:" << born << "	   "
			<< "Died:" << died << endl
			<< "	Live for: " << Counter << "sec" << endl;
	}
	else if(number == 3)
	{
		
		ofstream HighScor("High_Scor.txt");
		ss_High_Scor.str("");
		ss_High_Scor << "High Scor:" << endl
			<< "Live:" << high_live << "	 "
			<< "Dead:" << 2500 - high_live << endl
			<< "Born:" << high_born << "	   "
			<< "Died:" << high_died << endl
			<< "	Live for:" << high << "sec" << endl;
		HighScor << ss_High_Scor.str();
		HighScor.close();
	}
	


}

void Huge_Screen::Draw()
{
	set_size();
	set_position();
	set_prev_gen();
	set_Cells();//tu su mi podatci tko je umro tko je ziv itd...
	Counter += 2;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			Cell.setOutlineColor(sf::Color::Red);
			Cell.setOutlineThickness(2);
			if (Cells[i][j])
			{
				Cell.setFillColor(sf::Color::Green);
			}
			else
			{
				Cell.setFillColor(sf::Color(192, 192, 192));
			}
			Window->draw(set_Cell());
			
		}
		Cell_position.x += size.x * 2;
		Cell_position.y = height * 0.2 + size.y;
	}
	set_this_gen();
	set_High_Scor();
	Window->draw(This_Gen);
	Window->draw(Prev_Gen);
	Window->draw(High_Scor);
}
