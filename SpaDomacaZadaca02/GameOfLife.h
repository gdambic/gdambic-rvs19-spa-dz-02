#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class GameOfLife
{
public:
	GameOfLife(sf::RenderWindow* window, int screen_width, int screen_height, char flag);
	void set_speed(char s);
	void draw();
private:
	void draw_environment();
	void next_generation();
	void check_life(int& life_count, int i, int j, char flag);
	bool create_life(int& life_count, int i, int j);
	void random_world();
	void draw_life(sf::Vector2f w);
	void draw_row(vector<bool> row, sf::Vector2f w);
	bool gen_rand_n();
	void open_world(string world_name);
	sf::RenderWindow* window;
	sf::Clock clock;
	float speed = 0.4f;
	int screen_width;
	int screen_height;
	const float life_size = 10.f;
	vector<vector<bool>> world;
	vector<vector<bool>> temp;
};
