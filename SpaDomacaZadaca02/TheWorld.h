#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <list>
#include <iostream>
#include <random>

#include <exception>

/*
This world will consist of chunks. Each chunk has 10000 points (100*100). Each chunk has a location expressed in intXY. Things bigger than max int are discarded.
When a new chunk is made it contacts its neighbours and sets itself as their neighbour, so they can contact it when dealing with edge pixels.
*/

//Chunks could be multithreaded.

class TheWorld
{
private:
	//grandfather clock tick tock
//	sf::SoundBuffer tick_buffer;
//	sf::Sound tick;
//	sf::SoundBuffer tock_buffer;
//	sf::Sound tock;
//	sf::Music music;//vivaldi four seasons? Time-themed so it's fitting.

	//Settings, can be changed from main
	bool show_chunks = false;
	int num_of_rebuild_chunks = 1;

	sf::Texture output_texture;
	sf::Sprite output;

	sf::RectangleShape surround_rectangle;

	static const int chunk_size = 100;//100 default
	static const int world_default_position = 15000;//100 default

	//This was a horrible idea. I regret everything.
	struct Chunk {
	private:
		int position_x = 0;
		int position_y = 0;
		//should not exceed 10,000 (w/ chunk size of 100)
		int num_things = 0;

		TheWorld* this_world;

		Chunk* up_neighbour = nullptr;//Y = 0
		Chunk* right_neighbour = nullptr;//X = 99
		Chunk* bottom_neighbour = nullptr;// Y = 99
		Chunk* left_neighbour = nullptr;// X = 0

		Chunk* up_left_neighbour = nullptr;
		Chunk* up_right_neighbour = nullptr;
		Chunk* bottom_right_neighbour = nullptr;
		Chunk* bottom_left_neighbour = nullptr;

		//So you might be wondering: man, why do we have two of them? Well, you see, while we're running calculations we need somewhere to store changes without
		//making the calculation confuse itself - we would be calculating for atoms which haven't been born / killed yet. So first we calculate stuff, and then later
		//we sync them up - simple as.
		bool* current_container = nullptr;
		//Buffer container for the next step
		bool* next_container = nullptr;
		
		//This will be a lot faster to draw than recalculating everything again every frame lol. Has to be cleared and rebuilt every time the user draws on it :(
		//Defined in constructor
		sf::Vertex white_point;
		sf::VertexArray triangles;
		sf::VertexArray points;

	public:

		void prepare_for_draw() {
			triangles.clear();
			points.clear();

			if (!has_things()) {
				return;
			}

			int pos_x = get_position_x() * chunk_size;
			int pos_y = get_position_y() * chunk_size;

			double square_spacing = 0.1;

			//now we do the rest
			for (size_t y = 0; y < chunk_size; y++) {
				for (size_t x = 0; x < chunk_size; x++) {
					if (get_current(x, y)) {
						//Performance mode (big zoomout) uses these
						white_point.position = sf::Vector2f(pos_x + x, pos_y + y);
						points.append(white_point);

						//Quads are not supported on some devices anymore, so we have to use triangles :(
						white_point.position = sf::Vector2f(pos_x + x + square_spacing, pos_y + y + square_spacing);
						triangles.append(white_point);
						white_point.position = sf::Vector2f(pos_x + x + 1 - square_spacing, pos_y + y + square_spacing);
						triangles.append(white_point);
						white_point.position = sf::Vector2f(pos_x + x + 1 - square_spacing, pos_y + y + 1 - square_spacing);
						triangles.append(white_point);

						white_point.position = sf::Vector2f(pos_x + x + 1 - square_spacing, pos_y + y + 1 - square_spacing);
						triangles.append(white_point);
						white_point.position = sf::Vector2f(pos_x + x + square_spacing, pos_y + y + 1 - square_spacing);
						triangles.append(white_point);
						white_point.position = sf::Vector2f(pos_x + x + square_spacing, pos_y + y + square_spacing);
						triangles.append(white_point);
					}
				}
			}
		}
		void do_draw(sf::RenderWindow& window, bool cheap_draw) {
			if (cheap_draw)	{
				window.draw(points);
				return;
			}
			window.draw(triangles);
		}

		int get_position_x() {
			return position_x;
		}
		int get_position_y() {
			return position_y;
		}

		bool has_things() {
			return (num_things != 0);
		}

		bool get_current(int x, int y) {
			return current_container[chunk_size * y + x];
		}

		void write_next(int x, int y, bool status){

			if (next_container[chunk_size * y + x] != status) {
				next_container[chunk_size * y + x] = status;
				if (status) {
					num_things++;
				}
				else {
					num_things--;
				}
			}
		}

		void write_direct(int x, int y, bool status, bool skip_draw = 0) {
			write_next(x, y, status);
			current_container[chunk_size * y + x] = status;

			//EXPENSIVE!
			if (skip_draw) return;
			prepare_for_draw();
		}

		bool should_terminate() {
			if (!has_things()) {
				//We only need to check our direct neighbours, if we have a diagonal connection there will always only be one connection, which
				//is not enough to create life.

				if ((up_neighbour != nullptr && up_neighbour->has_things()) || (right_neighbour != nullptr && right_neighbour->has_things()) ||
					(bottom_neighbour != nullptr && bottom_neighbour->has_things()) || (left_neighbour != nullptr && left_neighbour->has_things())) {
					return 0;
				}
				return 1;
			}
			return 0;
		}

		/// <param name="dir (1 = UP, 2 = RIGHT, 3 = BOTTOM, 4 = LEFT, 5 = UP_LEFT, 6 = UP_RIGHT, 7 = BOT_RIGHT, 8 = BOT_LEFT)"></param>
		void add_neighbour(char dir, Chunk* chunk) {
			switch (dir)
			{
			case 1:
				up_neighbour = chunk;
				break;
			case 2:
				right_neighbour = chunk;
				break;
			case 3:
				bottom_neighbour = chunk;
				break;
			case 4:
				left_neighbour = chunk;
				break;
			case 5:
				up_left_neighbour = chunk;
				break;
			case 6:
				up_right_neighbour = chunk;
				break;
			case 7:
				bottom_right_neighbour = chunk;
				break;
			case 8:
				bottom_left_neighbour = chunk;
				break;
			default:
				std::cout << "Unexpected behaviour in TheWorld::Chunk::add_neighbour (nonsense input: " << dir << ")." << std::endl;
				exit(1);
				break;
			}
		}

		void remove_neighbour(Chunk* chunk) {
			if (chunk == up_neighbour){
				up_neighbour = nullptr;
				return;
			}
			else if (chunk == right_neighbour) {
				right_neighbour = nullptr;
				return;
			}
			else if (chunk == bottom_neighbour) {
				bottom_neighbour = nullptr;
				return;
			}
			else if (chunk == left_neighbour) {
				left_neighbour = nullptr;
				return;
			}
			else if (chunk == up_left_neighbour) {
				up_left_neighbour = nullptr;
				return;
			}
			else if (chunk == up_right_neighbour) {
				up_right_neighbour = nullptr;
				return;
			}
			else if (chunk == bottom_right_neighbour) {
				bottom_right_neighbour = nullptr;
				return;
			}
			else if (chunk == bottom_left_neighbour) {
				bottom_left_neighbour = nullptr;
				return;
			}

			should_terminate();
		}

		void do_point_neighbour_logic(int x, int y, int neighbours) {
			if (get_current(x, y)) {
				if (neighbours < 2 || neighbours > 3) {
					write_next(x, y, false);
				}
			}
			else {
				if (neighbours == 3) {
					write_next(x, y, true);
				}
			}
		}

		void check_border_point(int x, int y) {//NOT OPTIMIZED, DUPLICATE CHECKS
			int neighbours = 0;
			{
				bool do_up = true;
				bool do_right = true;
				bool do_bottom = true;
				bool do_left = true;

				bool do_up_left = true;
				bool do_up_right = true;
				bool do_bottom_right = true;
				bool do_bottom_left = true;

				{//Checking if we're on the edges of the chunk, and getting neighbours from them
					if (x == 0) {
						do_left = false;
						do_up_left = false;
						do_bottom_left = false;
						if (left_neighbour != nullptr) {
							if (left_neighbour->get_current(chunk_size - 1, y)) {
								neighbours++;
							}
							if (y != chunk_size - 1 && left_neighbour->get_current(chunk_size - 1, y + 1)) {
								neighbours++;
							}
							if (y != 0 && left_neighbour->get_current(chunk_size - 1, y - 1)) {
								neighbours++;
							}
						}
					}
					if (y == 0) {
						do_up = false;
						do_up_right = false;
						do_up_left = false;
						if (up_neighbour != nullptr){
							if (up_neighbour->get_current(x, chunk_size - 1)) {
								neighbours++;
							}
							if (x != chunk_size - 1 && up_neighbour->get_current(x + 1, chunk_size - 1)) {
								neighbours++;
							}
							if (x != 0 && up_neighbour->get_current(x - 1, chunk_size - 1)) {
								neighbours++;
							}
						}
					}
					if (x == chunk_size - 1) {
						do_right = false;
						do_up_right = false;
						do_bottom_right = false;
						if (right_neighbour != nullptr) {
							if (right_neighbour->get_current(0, y)) {
								neighbours++;
							}
							if (y != chunk_size - 1 && right_neighbour->get_current(0, y + 1)) {
								neighbours++;
							}
							if (y != 0 && right_neighbour->get_current(0, y - 1)) {
								neighbours++;
							}
						}
					}
					if (y == chunk_size - 1) {
						do_bottom = false;
						do_bottom_left = false;
						do_bottom_right = false;
						if (bottom_neighbour != nullptr) {
							if (bottom_neighbour->get_current(x, 0)) {
								neighbours++;
							}
							if (x != chunk_size - 1 && bottom_neighbour->get_current(x + 1, 0)) {
								neighbours++;
							}
							if (x!= 0 && bottom_neighbour->get_current(x - 1, 0)) {
								neighbours++;
							}
						}
					}
					//diagonal
					if (x == 0 && y == 0) {
						if (up_left_neighbour != nullptr && up_left_neighbour->get_current(chunk_size - 1, chunk_size - 1)) {
							neighbours++;
						}
					}
					if (x == chunk_size - 1 && y == 0) {
						if (up_right_neighbour != nullptr && up_right_neighbour->get_current(0, chunk_size - 1)) {
							neighbours++;
						}
					}
					if (x == chunk_size - 1 && y == chunk_size - 1) {
						if (bottom_right_neighbour != nullptr && bottom_right_neighbour->get_current(0, 0)) {
							neighbours++;
						}
					}
					if (x == 0 && y == chunk_size - 1) {
						if (bottom_left_neighbour != nullptr && bottom_left_neighbour->get_current(chunk_size - 1, 0)) {
							neighbours++;
						}
					}

				}//

				{//
					if (do_up) {
						if (get_current(x, y - 1)) {
							neighbours++;
						}
					}
					if (do_right) {
						if (get_current(x + 1, y)) {
							neighbours++;
						}
					}
					if (do_bottom) {
						if (get_current(x, y + 1)) {
							neighbours++;
						}
					}
					if (do_left) {
						if (get_current(x - 1, y)) {
							neighbours++;
						}
					}
					//diagonal
					if (do_up_left) {
						if (get_current(x - 1, y - 1)) {
							neighbours++;
						}
					}
					if (do_up_right) {
						if (get_current(x + 1, y - 1)) {
							neighbours++;
						}
					}
					if (do_bottom_right) {
						if (get_current(x + 1, y + 1)) {
							neighbours++;
						}
					}
					if (do_bottom_left) {
						if (get_current(x - 1, y + 1)) {
							neighbours++;
						}
					}
				}//
			}

			do_point_neighbour_logic(x, y, neighbours);
		}

		void check_point(int x, int y) {
			int neighbours = 0;

			if (get_current(x, y - 1)) {
				neighbours++;
			}
			if (get_current(x + 1, y)) {
				neighbours++;
			}
			if (get_current(x, y + 1)) {
				neighbours++;
			}
			if (get_current(x - 1, y)) {
				neighbours++;
			}
			//diagonal
			if (get_current(x - 1, y - 1)) {
				neighbours++;
			}
			if (get_current(x + 1, y - 1)) {
				neighbours++;
			}
			if (get_current(x + 1, y + 1)) {
				neighbours++;
			}
			if (get_current(x - 1, y + 1)) {
				neighbours++;
			}

			do_point_neighbour_logic(x, y, neighbours);
		}

		//Sync everything up before moving to calculations
		void tick_prepare() {

			for (size_t y = 0; y < chunk_size; y++)
			{
				for (size_t x = 0; x < chunk_size; x++)
				{
					current_container[chunk_size * y + x] = next_container[chunk_size * y + x];
				}
			}
			prepare_for_draw();
		}
		void tick_perform() {
			//Special checks for chunk borders
			for (size_t y = 0; y < chunk_size; y++) {// for x = 0
				check_border_point(0, y);
			}
			for (size_t y = 0; y < chunk_size; y++) {// for x = chunk_size
				check_border_point(chunk_size - 1, y);
			}
			for (size_t x = 1; x < chunk_size - 1; x++) {// for y = 0
				check_border_point(x, 0);
			}
			for (size_t x = 1; x < chunk_size - 1; x++) {// for y = chunk_size
				check_border_point(x, chunk_size - 1);
			}

			if (!has_things()) {
				return;
			}
			//now we do the rest
			for (size_t y = 1; y < chunk_size - 1; y++) {
				for (size_t x = 1; x < chunk_size - 1; x++) {
					check_point(x, y);
				}
			}
		}

		//0 = OK, 1 = UP, 2 = RIGHT, 3 = BOTTOM, 4 = LEFT. No diagonals.
		//Usage is in world processing, if it passes has_things it needs to have neighbours so they can take on any spillover
		int get_missing_neighbour(){

			if (up_neighbour == nullptr) {
				return 1;
			}
			if (right_neighbour == nullptr) {
				return 2;
			}
			if (bottom_neighbour == nullptr) {
				return 3;
			}
			if (left_neighbour == nullptr) {
				return 4;
			}
			return 0;
		}

		void randomize_chunk() {
			std::random_device rd;
			std::mt19937 random_gen{ rd() };

			for (size_t y = 0; y < chunk_size; y++)
			{
				for (size_t x = 0; x < chunk_size; x++)
				{
					if (random_gen() % 4 == 3) {
						write_direct(x, y, true, true);
					}
				}
			}
			prepare_for_draw();
		}

		//should only be called by emplace_back in the below chunks list
		Chunk(int x, int y, TheWorld& world) {
			current_container = new bool[chunk_size * chunk_size] {0};
			next_container = new bool[chunk_size * chunk_size] {0};

			white_point = sf::Vertex(sf::Vector2f(0, 0), sf::Color::White);
			triangles = sf::VertexArray(sf::Triangles);
			points = sf::VertexArray(sf::Points);

			this_world = &world;
			position_x = x;
			position_y = y;

			for (Chunk& chunk : world.chunks)//check for neighbours
			{
				if (chunk.position_x == position_x) {
					if (chunk.position_y == position_y + 1) {//below
						add_neighbour(3, &chunk);
						chunk.add_neighbour(1, this);
					}
					if (chunk.position_y == position_y - 1) {//above
						add_neighbour(1, &chunk);
						chunk.add_neighbour(3, this);
					}
					continue;
				}
				if (chunk.position_y == position_y) {
					if (chunk.position_x == position_x + 1) {//right
						add_neighbour(2, &chunk);
						chunk.add_neighbour(4, this);
					}
					if (chunk.position_x == position_x - 1) {//left
						add_neighbour(4, &chunk);
						chunk.add_neighbour(2, this);
					}
					continue;
				}
				if (chunk.position_y == position_y - 1 && chunk.position_x == position_x - 1) {
					add_neighbour(5, &chunk);
					chunk.add_neighbour(7, this);
				}
				if (chunk.position_y == position_y - 1 && chunk.position_x == position_x + 1) {
					add_neighbour(6, &chunk);
					chunk.add_neighbour(8, this);
				}
				if (chunk.position_y == position_y + 1 && chunk.position_x == position_x + 1) {
					add_neighbour(7, &chunk);
					chunk.add_neighbour(5, this);
				}
				if (chunk.position_y == position_y + 1 && chunk.position_x == position_x - 1) {
					add_neighbour(8, &chunk);
					chunk.add_neighbour(6, this);
				}
			}
		}


		//report to neighbours and abandon ship
		~Chunk() {
			if (up_neighbour != nullptr)
				up_neighbour->remove_neighbour(this);
			if (right_neighbour != nullptr)
				right_neighbour->remove_neighbour(this);
			if (bottom_neighbour != nullptr)
				bottom_neighbour->remove_neighbour(this);
			if (left_neighbour != nullptr)
				left_neighbour->remove_neighbour(this);

			if (up_left_neighbour != nullptr)
				up_left_neighbour->remove_neighbour(this);
			if (up_right_neighbour != nullptr)
				up_right_neighbour->remove_neighbour(this);
			if (bottom_left_neighbour != nullptr)
				bottom_left_neighbour->remove_neighbour(this);
			if (bottom_right_neighbour != nullptr)
				bottom_right_neighbour->remove_neighbour(this);

			//goodbye cruel world
			delete[] current_container;
			delete[] next_container;
		}

		//Chunk(Chunk& chunk) = delete;//no

		/*
		Chunk(Chunk& chunk)//*sigh
		{
			this_world = new nullptr;
			this_world = chunk.this_world;//pointer galore
			current_container = new bool[chunk_size * chunk_size] {0};
			next_container = new bool[chunk_size * chunk_size] {0};

			for (size_t y = 0; y < chunk_size; y++)
			{
				for (size_t x = 0; x < chunk_size; x++)
				{
					next_container[chunk_size * y + x] = chunk.next_container[chunk_size * y + x];
					current_container[chunk_size * y + x] = chunk.current_container[chunk_size * y + x];
				}
			}
			return;
			this_world = &(*chunk.this_world);//pointer galore
			current_container = new bool[chunk_size * chunk_size] {0};
			next_container = new bool[chunk_size * chunk_size] {0};

			for (size_t y = 0; y < chunk_size; y++)
			{
				for (size_t x = 0; x < chunk_size; x++)
				{
					next_container[chunk_size * y + x] = chunk.next_container[chunk_size * y + x];
					current_container[chunk_size * y + x] = chunk.current_container[chunk_size * y + x];
				}
			}
		}*/
	};

	std::list<Chunk> chunks;


public:
	TheWorld();
	void do_tick();
	void draw(sf::RenderWindow& window, double zoom);
	void rebuild();
	void toggle_show_chunks();
	void set_dot(int x, int y, bool state);
	int get_world_default_position();
	void increment_rebuild_chunk_number();
	void decrement_rebuild_chunk_number();
	int get_rebuild_chunk_number();
};

