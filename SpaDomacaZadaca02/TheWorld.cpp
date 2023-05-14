#include "TheWorld.h"
#include "SFML/System/Vector2.hpp"

#include <random>
#include <vector>
#include <math.h>
#include <algorithm>

#include <thread>

TheWorld::TheWorld()
{
	chunks.emplace_back(get_world_default_position() / chunk_size, get_world_default_position() / chunk_size, *this);

	chunks.front().randomize_chunk();

	surround_rectangle.setFillColor(sf::Color(0,0,0,0));
	surround_rectangle.setOutlineColor(sf::Color::Cyan);
	surround_rectangle.setOutlineThickness(-1);
	surround_rectangle.setSize(sf::Vector2f(chunk_size, chunk_size));
}

void TheWorld::do_tick()
{
	if (chunks.size() == 0) {
		return;
	}

	for (auto& chunk : chunks)
	{
		if (chunk.has_things() && chunk.get_position_x() < 30000 / chunk_size && chunk.get_position_x() > 0 &&
			chunk.get_position_y() < 30000 / chunk_size && chunk.get_position_y() > 0) {
			int check = chunk.get_missing_neighbour();
			while (check != 0) {
				switch (check) {
				case 1:
					chunks.emplace_back(chunk.get_position_x(), chunk.get_position_y() - 1, *this);
					break;
				case 2:
					chunks.emplace_back(chunk.get_position_x() + 1, chunk.get_position_y(), *this);
					break;
				case 3:
					chunks.emplace_back(chunk.get_position_x(), chunk.get_position_y() + 1, *this);
					break;
				case 4:
					chunks.emplace_back(chunk.get_position_x() - 1, chunk.get_position_y(), *this);
					break;
				}
				check = chunk.get_missing_neighbour();
			}
		}

	}

	std::vector<std::thread> thread_vec;

	for (auto& chunk : chunks)
	{
		//does all the calculations and saves them in a buffer to avoid overwrites
		thread_vec.emplace_back(&TheWorld::Chunk::tick_perform, &chunk);
	}

	for (auto& thread : thread_vec)
	{
		thread.join();
	}
	thread_vec.clear();

	for (auto& chunk : chunks)
	{
		//moves everything from the buffer into the current point array
		thread_vec.emplace_back(&TheWorld::Chunk::tick_prepare, &chunk);
	}

	for (auto& thread : thread_vec)
	{
		thread.join();
	}
	thread_vec.clear();

	for (auto it = chunks.begin(); it != chunks.end(); it++)
	{
		if (chunks.size() == 0) {
			break;
		}
		if (it->should_terminate())
		{
			it = chunks.erase(it);
			if (it == chunks.end())
				break;
		}
	}
}

//Zoom is used to determine if a performance optimization for drawing is needed
void TheWorld::draw(sf::RenderWindow& window, double zoom)
{

	if (chunks.size() == 0)
	{
		std::cout << "What?" << std::endl;
		return;
	}

	if (show_chunks)
	{
		for (auto& chunk : chunks)
		{
			int pos_x = chunk.get_position_x() * chunk_size;
			int pos_y = chunk.get_position_y() * chunk_size;
			surround_rectangle.setPosition(pos_x, pos_y);
			if (chunk.has_things()) {
				surround_rectangle.setOutlineColor(sf::Color::Cyan);
			}
			else {
				surround_rectangle.setOutlineColor(sf::Color::Blue);
			}
			window.draw(surround_rectangle);
		}
	}

	bool do_cheap_draw = (zoom >= 0.7);//can't even tell at that zoom, so it's fine!
	for (auto& chunk : chunks)
	{
		chunk.do_draw(window, do_cheap_draw);
	}
}

void TheWorld::rebuild()
{
	while (!chunks.empty()) {
		chunks.pop_back();
	}

	int startpos = get_world_default_position() / chunk_size;
	
	for (size_t y = startpos; y < startpos + num_of_rebuild_chunks; y++)
	{
		for (size_t x = startpos; x < startpos + num_of_rebuild_chunks; x++)
		{
			chunks.emplace_back(x, y, *this);
		}
	}

	//Multithreading
	std::vector<std::thread> thread_vec;

	for (auto& chunk : chunks)
	{
		thread_vec.emplace_back(&TheWorld::Chunk::randomize_chunk, &chunk);
	}

	for (auto& thread : thread_vec)
	{
		thread.join();
	}
	thread_vec.clear();
}

void TheWorld::toggle_show_chunks()
{
	show_chunks = !show_chunks;
}

void TheWorld::set_dot(int x, int y, bool state)
{
	int chunk_locate_x = x;
	int chunk_locate_y = y;

	if (chunk_locate_x < 0) {
		//x -= 1;
		chunk_locate_x -= chunk_size;
	}
	if (chunk_locate_y < 0) {
		//y -= 1;
		chunk_locate_y -= chunk_size;
	}

	chunk_locate_x /= chunk_size;
	chunk_locate_y /= chunk_size;

	std::cout << "START" << chunk_locate_x << ", " << chunk_locate_y << std::endl;
	
	std::cout << chunk_locate_x << ", " << chunk_locate_y << std::endl;

	for (auto& chunk : chunks)
	{
		if (chunk.get_position_x() == chunk_locate_x && chunk.get_position_y() == chunk_locate_y) {
			chunk.write_direct(x - chunk_locate_x * chunk_size, y - chunk_locate_y * chunk_size, state);
			return;
		}
	}

	chunks.emplace_back(chunk_locate_x, chunk_locate_y, *this);
	chunks.back().write_direct(x - chunk_locate_x * chunk_size, y - chunk_locate_y * chunk_size, state);
}

int TheWorld::get_world_default_position()
{
	return world_default_position;
}

void TheWorld::increment_rebuild_chunk_number()
{
	if (num_of_rebuild_chunks < INT_MAX - 1)
		num_of_rebuild_chunks++;
}

void TheWorld::decrement_rebuild_chunk_number()
{
	if (num_of_rebuild_chunks > 0)
		num_of_rebuild_chunks--;
}

int TheWorld::get_rebuild_chunk_number()
{
	return int(num_of_rebuild_chunks);
}
