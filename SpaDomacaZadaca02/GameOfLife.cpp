#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

GameOfLife::GameOfLife(sf::RenderWindow* window, int screen_width, int screen_height, char flag)
{
	this->window = window;
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	sf::Clock clock = this->clock;

	srand(time(nullptr));

	switch (flag)
	{
	case '1':
		random_world();
		break;
	case '2':
		open_world("world_a.txt");
		break;
	case '3':
		open_world("world_b.txt");
		break;
	}
	//temp world
	temp = world;
}

void GameOfLife::set_speed(char s)
{
	switch (s)
	{
	case '+':
		if (speed > 0.3f)
		{
			speed -= 0.2f;
		}
		else
		{
			speed = 0.0f;
		}
		cout << "Game speed : " << speed << " sec" << endl;
		break;
	case '-':
		if (speed <=2.1f)
		{
			speed += 0.2f;
		}
		cout << "Game speed : " << speed << " sec" << endl;
		break;
	}
}

void GameOfLife::draw()
{	
	draw_environment();
	sf::Time elapsed = clock.getElapsedTime();
	float sec = elapsed.asSeconds();
	if (sec >= speed)
	{
		next_generation();
		clock.restart();		
	}
	else
	{
		draw_environment();
	}
}

void GameOfLife::draw_environment()
{
	// initial drawing coordinates
	sf::Vector2f w;
	w.x = 0.f;
	w.y = 0.f;

	// draw row by row
	for (int i = 0; i < world.size(); i++)
	{
		draw_row(world[i], w);
		w.y += life_size;
	}
}

void GameOfLife::next_generation()
{
	int height = screen_height / life_size;
	int width = screen_width / life_size;
	int life_count = 0;

	for (int i = 0; i < height; i++) //rows [i]
	{	
		for (int j = 0; j < width; j++) //columns [j]
		{			
			// world edge top-bottom and corners
			if (i == 0)
			{
				if (j == 0)
				{	//corner top left				
					check_life(life_count, i, j, 'e');
					check_life(life_count, i, j, 'g');
					check_life(life_count, i, j, 'h');
					temp[i][j] = create_life(life_count, i, j);
				}
				else if (j == width - 1)
				{  //corner top right
					check_life(life_count, i, j, 'd');
					check_life(life_count, i, j, 'f');
					check_life(life_count, i, j, 'g');
					temp[i][j] = create_life(life_count, i, j);
				}
				else
				{
					check_life(life_count, i, j, 'd');
					check_life(life_count, i, j, 'e');
					check_life(life_count, i, j, 'f');
					check_life(life_count, i, j, 'g');
					check_life(life_count, i, j, 'h');
					temp[i][j] = create_life(life_count, i, j);
				}
			}
			else if (i == height - 1)
			{
				if (j == 0)
				{	//corner bot left				
					check_life(life_count, i, j, 'b');
					check_life(life_count, i, j, 'c');
					check_life(life_count, i, j, 'e');
					temp[i][j] = create_life(life_count, i, j);
				}
				else if (j == width - 1)
				{  //corner bot right
					check_life(life_count, i, j, 'a');
					check_life(life_count, i, j, 'b');
					check_life(life_count, i, j, 'd');
					temp[i][j] = create_life(life_count, i, j);
				}
				else
				{
					check_life(life_count, i, j, 'a');
					check_life(life_count, i, j, 'b');
					check_life(life_count, i, j, 'c');
					check_life(life_count, i, j, 'd');
					check_life(life_count, i, j, 'e');
					temp[i][j] = create_life(life_count, i, j);
				}
			}
			//world edge left-right
			else if (j == 0)
			{
				check_life(life_count, i, j, 'b');
				check_life(life_count, i, j, 'c');
				check_life(life_count, i, j, 'e');
				check_life(life_count, i, j, 'g');
				check_life(life_count, i, j, 'h');
				temp[i][j] = create_life(life_count, i, j);
			}
			else if (j == width - 1)
			{
				check_life(life_count, i, j, 'a');
				check_life(life_count, i, j, 'b');
				check_life(life_count, i, j, 'd');
				check_life(life_count, i, j, 'f');
				check_life(life_count, i, j, 'g');
				temp[i][j] = create_life(life_count, i, j);
			}
			else
			{				
				check_life(life_count, i, j, 'a');
				check_life(life_count, i, j, 'b');
				check_life(life_count, i, j, 'c');
				check_life(life_count, i, j, 'd');
				check_life(life_count, i, j, 'e');
				check_life(life_count, i, j, 'f');
				check_life(life_count, i, j, 'g');
				check_life(life_count, i, j, 'h');
				temp[i][j] = create_life(life_count, i, j);
			}
			life_count = 0;
		}
	}
	world = temp;	
}

void GameOfLife::check_life(int& life_count, int i, int j, char flag)
{	
	switch (flag)
	{
	case 'a':
		if (world[--i][--j])
		{
			life_count++;
		}
		break;
	case 'b':
		if (world[--i][j])
		{
			life_count++;
		}
		break;
	case 'c':
		if (world[--i][++j])
		{
			life_count++;
		}
		break;
	case 'd':
		if (world[i][--j])
		{
			life_count++;
		}
		break;
	case 'e':
		if (world[i][++j])
		{
			life_count++;
		}
		break;
	case 'f':
		if (world[++i][--j])
		{
			life_count++;
		}
		break;
	case 'g':
		if (world[++i][j])
		{
			life_count++;
		}
		break;
	case 'h':
		if (world[++i][++j])
		{
			life_count++;
		}
		break;
	}
}

bool GameOfLife::create_life(int& life_count, int i, int j)
{
	// live cells
	if (world[i][j])
	{
		if (life_count == 2 || life_count == 3)
		{	//next generation
			return true; //life!
		}
		else
		{	//underpopulation, overpopulation			
			return false; //empty
		}
	}
	// empty cells
	else
	{
		if (life_count == 3)
		{	//reproduction			
			return true; //life!
		}
		else
		{			
			return false; //empty
		}
	}
}

void GameOfLife::random_world()
{
	vector<bool> row(screen_width / life_size);

	for (int i = 0; i < screen_height / life_size; i++)
	{
		for (int j = 0; j < screen_width / life_size; j++)
		{
			row[j] = gen_rand_n();
		}
		world.push_back(row);
	}
}

void GameOfLife::draw_life(sf::Vector2f w)
{
	sf::Vector2f pixel(life_size, life_size);
	sf::RectangleShape life(pixel);
	life.setFillColor(sf::Color(255, 255, 255));
	life.setPosition(w.x, w.y);
	window->draw(life);
}

void GameOfLife::draw_row(vector<bool> row, sf::Vector2f w)
{
	for (int i = 0; i < row.size(); i++)
	{
		if (row[i] == 1)
		{
			draw_life(w);
			w.x += life_size;
		}
		else
		{
			w.x += life_size;
		}
	}
}

bool GameOfLife::gen_rand_n()
{
	int r = rand() % 4;
	if (r==1)
	{	// 25% chance for 1 life ("1")
		return 1;
	}
	else
	{	// 75% chance for 0,2,3 empty ("0")
		return 0;
	}	
}

void GameOfLife::open_world(string world_name)
{
	ifstream in(world_name);

	if (!in)
	{
		cout << "Something went wrong while opening the file: \"" << world_name << "\"" << endl;
	}

	vector<bool> row(screen_width / life_size);
	string line;
	string temp;

	for (int i = 0; i < screen_height / life_size; i++)
	{
		getline(in, line);
		stringstream ss(line);

		for (int j = 0; j < screen_width / life_size; j++)
		{
			getline(ss, temp, '-');
			row[j] = stoi(temp);
		}
		world.push_back(row);
	}
	in.close();
}

