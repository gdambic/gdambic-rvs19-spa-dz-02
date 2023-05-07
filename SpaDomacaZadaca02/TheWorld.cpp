#include "TheWorld.h"
#include "SFML/System/Vector2.hpp"

#include <random>
#include <vector>

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
			if (random_gen() % 4 == 1) {
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
		
		if (chunk.has_things()) {
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

	//How big should our texture be?
	for (auto& chunk : chunks)
	{
		int pos_x = chunk.get_position_x() * chunk_size;
		int pos_y = chunk.get_position_y() * chunk_size;
		surround_rectangle.setPosition(pos_x, pos_y);
		window.draw(surround_rectangle);
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
