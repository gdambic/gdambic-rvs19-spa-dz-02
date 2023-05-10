#pragma once
#include <SFML/Graphics.hpp>
#define MAX_ITEM_NUM 4

class game_menu
{
public:
	game_menu(float width, float height, std::string name_1, std::string name_2, std::string name_3, std::string name_4, bool centered);
	~game_menu();

	void randomise_font(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void center_check(float width, float height);
	void moveup();
	void movedown();
	int get_pressed_item() { return selected_item_index; }

private:
	bool center = false;
	int selected_item_index;
	sf::Font font;
	sf::Text menu_text[MAX_ITEM_NUM];
};