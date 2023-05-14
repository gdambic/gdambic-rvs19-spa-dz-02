#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <windows.h>

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
	void kill_cells(int x, int y, int no_of_cells_to_kill);
	void kill_all();
	void populate_cells(sf::Vector2i& mousePos);
	void next_gen();
	bool get_curr_gen(int i, int j);
	int get_generation_count();
	void set_generation_count(int n);
	float get_cell_size();
	int get_rows();
	int get_columns();
	void copy_next_to_curr();
	void big_boom(int pos_x, int pos_y);
};

struct cat
{
	sf::RectangleShape* catFalling;
	sf::Texture* catFallingTexture;
	sf::RectangleShape* scratches;
	sf::Texture* scratchesTexture;
	sf::RectangleShape* curious_1;
	sf::Texture* curious_1Texture;
	sf::RectangleShape* streach_2;
	sf::Texture* streach_2Texture;
	sf::RectangleShape* boom1;
	sf::Texture* boom1Texture;
	sf::RectangleShape* boom2;
	sf::Texture* boom2Texture;
	sf::RectangleShape* paw_prints;
	sf::Texture* paw_printsTexture;
	sf::RectangleShape* rm_dance;
	sf::Texture* rm_danceTexture;
	sf::RectangleShape* rm_middle_finger;
	sf::Texture* rm_middle_fingerTexture;
};

class draw_gol
{
private:
	sf::RenderWindow* window;
	game_of_life* g;
	cat* c;
	sf::Font font;
	int gen_rnd(int min, int max);
	std::string cwd;
public:
	draw_gol(sf::RenderWindow* window, std::string cwd);
	void watch_gol();
	void mouse_clicked_left(sf::Vector2i& mousePos);
	void mouse_clicked_right(sf::Vector2i& mousePos);
	int need_generation_count();
	void init_cat();
	void cat_falling(int start, int finish);
	void scratching(int start, int finish);
	void curious_streach(int start, int finish);
	void call_big_boom(int pos_x, int pos_y, int when);
	void boom(int start, int finish);
	void write_text_to_screen(string text, int posX, int posY);
	void write_text_to_screen(string text, int posX, int posY, int start, int finish);
	void rm_dance(int start, int finish);
	void call_kill_all(int when);
	void rm_middle_finger(int start, int finish);
	
};

