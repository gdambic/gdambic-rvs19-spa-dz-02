#include "TheWorld.h"
#include "SFML/System/Vector2.hpp"

#include <random>
#include <vector>
#include <math.h>

TheWorld::TheWorld()
{
	std::random_device rd;
	random_gen = std::mt19937{ rd() };
	//random_gen() % num

	chunks.emplace_back(0, 0, *this);

	for (size_t y = 0; y < chunk_size; y++)
	{
		for (size_t x = 0; x < chunk_size; x++)
		{
			if (random_gen() % 4 == 3) {
				chunks.front().write_at(x, y, true);
			}
		}
	}

	default_rectangle.setFillColor(sf::Color::White);
	default_rectangle.setSize(sf::Vector2f(1, 1));

	surround_rectangle.setFillColor(sf::Color(0,0,0,0));
	surround_rectangle.setOutlineColor(sf::Color::Cyan);
	surround_rectangle.setOutlineThickness(1);
	surround_rectangle.setSize(sf::Vector2f(chunk_size, chunk_size));
}

void TheWorld::do_tick()
{
	if (chunks.size() == 0) {
		return;
	}

	for (auto& chunk : chunks)
	{
		chunk.tick_prepare();
		
		if (chunk.has_things() && abs(chunk.get_position_x()) < INT_MAX - 1000 && abs(chunk.get_position_y()) < INT_MAX - 1000) {
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

	for (auto& chunk : chunks)
	{
		chunk.tick_perform();
	}

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

void TheWorld::draw(sf::RenderWindow& window)
{
	int min_x = INT_MAX;
	int min_y = INT_MAX;
	int max_x = INT_MIN;
	int max_y = INT_MIN;

	if (chunks.size() == 0)
	{
		std::cout << "Nothing left";
		return;
	}

	if (show_chunks)
	{
		for (auto& chunk : chunks)
		{
			int pos_x = chunk.get_position_x() * chunk_size;
			int pos_y = chunk.get_position_y() * chunk_size;
			surround_rectangle.setPosition(pos_x, pos_y);
			window.draw(surround_rectangle);
		}
	}

	for (auto& chunk : chunks)
	{
		int pos_x = chunk.get_position_x() * chunk_size;
		int pos_y = chunk.get_position_y() * chunk_size;

		for (int y = 0; y < chunk_size; y++)
		{
			for (int x = 0; x < chunk_size; x++)
			{
				if (chunk.get_at(x, y)) {
					default_rectangle.setPosition(pos_x + x, pos_y + y);
					window.draw(default_rectangle);
				}
			}
		}
	}
}

void TheWorld::rebuild()
{
	while (!chunks.empty()) {
		chunks.pop_back();
	}
	
	for (size_t y = 0; y < chunks_to_start_with; y++)
	{
		for (size_t x = 0; x < chunks_to_start_with; x++)
		{
			chunks.emplace_back(x, y, *this);
		}
	}

	for (auto& chunk : chunks)
	{
		for (size_t y = 0; y < chunk_size; y++)
		{
			for (size_t x = 0; x < chunk_size; x++)
			{
				if (random_gen() % 4 == 3) {
					chunk.write_at(x, y, true);
				}
			}
		}
	}
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
		chunk_locate_x -= chunk_size;
	}
	if (chunk_locate_y < 0) {
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
