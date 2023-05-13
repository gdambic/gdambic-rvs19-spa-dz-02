#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class game_of_life
{
private:
	static const unsigned int columns = 108; // 1080
	static const unsigned int rows = 192; // 1920
	float cell_size = 10.0f;
	bool _curr_gen[rows][columns];
	bool _next_gen[rows][columns];
	int generation_counter = 0;
	int gen_rnd();
public:
	game_of_life();
	void kill_cells(sf::Vector2i& mousePos);
	void populate_cells(sf::Vector2i& mousePos);
	void next_gen();
	bool get_curr_gen(int i, int j);
	int get_generation_count();
	void set_generation_count(int n);
	float get_cell_size();
	int get_rows();
	int get_columns();
	void copy_curr_to_next();
};

class draw_gol
{
private:
	sf::RenderWindow* window;
	game_of_life* g;
	int gen_rnd(int min, int max);
public:
	draw_gol(sf::RenderWindow* window);
	void watch_gol();
	void mouse_clicked_left(sf::Vector2i& mousePos);
	void mouse_clicked_right(sf::Vector2i& mousePos);
	int need_generation_count();
};