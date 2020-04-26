#include "Small_Screen.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

Small_Screen::Small_Screen(sf::RenderWindow* window)
{
	place = 0;
	memset(check_cell, 1, 8 * 4 * sizeof(bool));
	this->Window = window;
	FirstTime = true;
	set_cell_size();
	live.setOutlineThickness(5);
	live.setOutlineColor(sf::Color::Green);
	live.setSize(cell_size);
	set_cell_size();
	/*dead.setOutlineThickness(5);
	dead.setOutlineColor(sf::Color::Red);
	dead.setSize(cell_size);*/
	set_cellposition();
}

void Small_Screen::set_cellposition()
{
	sf::Vector2f start_position;
	start_position.x = (Window->getSize().x / 16) - 20;
	start_position.y = Window->getSize().y * 0.2;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cells_position[i][j] = start_position;
			start_position.y += cell_size.y * 2;
		}
		start_position.x += cell_size.x * 2;
		start_position.y = Window->getSize().y * 0.2;
	}
}

void Small_Screen::set_cell_size()
{
	cell_size.x = Window->getSize().x / 16;
	cell_size.y = (Window->getSize().y * 0.8) / 8;
	set_cellposition();
}
//napravio si prvi put da upise tko je ziv tko mrtav i stavio velicinu cella sad dalje trebas derati
void Small_Screen::set_cell()
{
	if (FirstTime)
	{
		srand(time(nullptr));
		int broj;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				broj = rand() % 4 + 1;
				if (broj == 4)
				{
					cells[i][j] = true;
		
				}
				else
				{
					cells[i][j] = false;
				}
			}
		}
	}

	else
	{
		memcpy(prev_cells, cells, 8 * 8 * sizeof(bool));


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int counter = 0;
				if (i - 1 >= 0 && j - 1 >= 0)
				{
					if (prev_cells[i - 1][j - 1])
					{
						counter++;
					}
				}
				if (j - 1 >= 0)
				{
					if (prev_cells[j - 1])
					{
						counter++;
					}
				}
				if (i + 1 < 8 && j - 1 >= 0)
				{
					if (prev_cells[i + 1][j - 1])
					{
						counter++;
					}
				}
				if (i + 1 < 8)
				{
					if (prev_cells[i + 1][j])
					{
						counter++;
					}
				}
				if (i + 1 < 8 && j + 1 < 4)
				{
					if (prev_cells[i + 1][j + 1])
					{
						counter++;
					}
				}
				if (j + 1 < 4)
				{
					if (prev_cells[i][j + 1])
					{
						counter++;
					}
				}
				if (i - 1 >= 0 && j + 1 < 4)
				{
					if (prev_cells[i - 1][j + 1])
					{
						counter++;
					}
				}
				if (i - 1 >= 0)
				{
					if (prev_cells[i - 1][j])
					{
						counter++;
					}
				}
				if (cells[i][j])
				{
					if (counter > 3 || counter < 2)
					{
						cells[i][j] = false;
						check_cell[i][j] = false;
					}	
				}
				if(cells[i][j] == false)
				{
					if (counter == 3)
					{
						cells[i][j] = true;
					}
				}
				counter = 0;
			}
		}
	}

	FirstTime = false;
}

void Small_Screen::set_cells()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (check_cell[i][j] == false)
			{
				if (players_position[j].x <  cells_position[i][j].x * 0.6 && players_position[j].x > cells_position[i][j].x * 0.4)
				{
					dead.setPosition(cells_position[i][j]);
					Window->draw(dead);
					check_cell[i][j] = true;
				}
				else
				{
					sf::RectangleShape died(sf::Vector2f(cell_size.x, 5));
					died.setFillColor(sf::Color::Red);
					died.setPosition(cells_position[i][j]);
					Window->draw(died);
					died.setRotation(90);
					died.setPosition(died.getPosition() + sf::Vector2f(cell_size.x, 0));
					died.setSize(sf::Vector2f(cell_size.y, 5));
					Window->draw(died);//radi
					died.setPosition(died.getPosition() + sf::Vector2f(0, cell_size.y));
					died.setRotation(180);
					died.setSize(sf::Vector2f(cell_size.x * 0.4, 5));//radi
					Window->draw(died);
					died.setPosition(died.getPosition() - sf::Vector2f(cell_size.x * 0.6, 0));
					died.setRotation(180);
					Window->draw(died);
					died.setPosition(died.getPosition() - sf::Vector2f(cell_size.x * 0.4, 0));
					died.setSize(sf::Vector2f(cell_size.y, 5));
					died.setRotation(-90);
					Window->draw(died);
					check_cell[i][j] = true;//maknuti nakon sto player-a napravis
				}
			}
			else
			{
				if (cells[i][j])
				{
					live.setPosition(cells_position[i][j]);
					Window->draw(live);

				}
				else
				{
					dead.setPosition(cells_position[i][j]);
					Window->draw(dead);
				}
			}
		}
	}

}


//treba ici prije stavljanja firsttime u false
void Small_Screen::set_playerposition()
{
	if (FirstTime)
	{
		for (int i = 0; i < 4; i++)
		{
			players_position[i] = track_position[i] + sf::Vector2f(track.getSize().x / 2, 0);
		}
	}
	else
	{
		players_position[place].x += 0.1;
		sf::Event event;
		Window->pollEvent(event);
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (players_position[place].x > track_position[place].x)
				{
					players_position[place].x -= 0.1;
				}
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				if (players_position[place].x < track_position[place].x)
				{
					players_position[place].x += 0.1;
				}
			}
		}
	}

	
}

void Small_Screen::set_player()
{
	for (int i = 0; i < 4; i++)
	{
		guardian.setPosition(players_position[i]);
		guardian.setFillColor(sf::Color::Red);
		guardian.setSize(sf::Vector2f(track.getSize().y * 0.5, track.getSize().y * 1.5));
		Window->draw(guardian);
	}

}

//stavio poziciju svake trake
void Small_Screen::set_positiontrack()
{
	for (int i = 0; i < 4; i++)
	{
		track_position[i] = cells_position[0][i] + sf::Vector2f(0, cell_size.y + cell_size.y * 0.2);
		track.setPosition(track_position[i]);
		track.setSize(sf::Vector2f(cell_size.x * 15, cell_size.y * 0.6));
		track.setFillColor(sf::Color::Yellow);
		track.setOutlineThickness(5);
		track.setOutlineColor(sf::Color(192, 192, 192));
		Window->draw(track);
	}


}



void Small_Screen::draw()
{
	set_positiontrack();
	set_playerposition();
	cout << "Samo odbija suradivati stoga sam odustao....." << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (check_cell[i][j] == false)
			{
				
				break;
			}
			else if (i == 7 && j == 3 )
			{
				set_cell();
			}
		}
	}
	set_cells();
	set_player();
	cout << place << endl;
}

