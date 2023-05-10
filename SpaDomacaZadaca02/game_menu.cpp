#include "game_menu.h"
#include "global.h"
/*
nemam volje da ovo komentiram, ali je u osnovi klasa koja upravlja i kreira menije
da, mogao sam bolje napraviti. mogao sam includati da sadrži druge ekterne "feature" kao nasumicna generacija boja menia
ali jednostavno nisam htjeo i u nekom trenutku sam bio isfrustriran jer neki featuri jednostavno nisu htjeli raditi

tko god hoce ovo popraviti ima moj blagoslov
*/
game_menu::game_menu(float width, float height, std::string name_1, std::string name_2, std::string name_3, std::string name_4, bool centered)
{
	font.loadFromFile("courier.ttf");
	menu_text[0].setFont(font);
	menu_text[0].setFillColor(sf::Color::Magenta);
	menu_text[0].setString(name_1);

	menu_text[1].setFont(font);
	menu_text[1].setFillColor(sf::Color::White);
	menu_text[1].setString(name_2);

	menu_text[2].setFont(font);
	menu_text[2].setFillColor(sf::Color::White);
	menu_text[2].setString(name_3);

	menu_text[3].setFont(font);
	menu_text[3].setFillColor(sf::Color::White);
	menu_text[3].setString(name_4);

	center = centered;

	center_check(width, height);

	selected_item_index = 0;
}

game_menu::~game_menu()
{
}

void game_menu::randomise_font(sf::RenderWindow& window)
{
	switch (get_rnd(1, 3))
	{
	case 1:
		font.loadFromFile("arial.ttf");
		break;
	case 2:
		font.loadFromFile("courier.ttf");
		break;
	case 3:
		font.loadFromFile("impact.ttf");
		break;
	};

	center_check(window.getSize().x, window.getSize().y);
}

void game_menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		window.draw(menu_text[i]);
	}
}

void game_menu::center_check(float width, float height)
{
	if (center == true)
	{
		sf::FloatRect bounds1 = menu_text[0].getLocalBounds();
		menu_text[0].setPosition(sf::Vector2f((width / 2) - (bounds1.width / 2), height / (MAX_ITEM_NUM + 1) * 1));
		sf::FloatRect bounds2 = menu_text[1].getLocalBounds();
		menu_text[1].setPosition(sf::Vector2f((width / 2) - (bounds2.width / 2), height / (MAX_ITEM_NUM + 1) * 2));
		sf::FloatRect bounds3 = menu_text[2].getLocalBounds();
		menu_text[2].setPosition(sf::Vector2f((width / 2) - (bounds3.width / 2), height / (MAX_ITEM_NUM + 1) * 3));
		sf::FloatRect bounds4 = menu_text[3].getLocalBounds();
		menu_text[3].setPosition(sf::Vector2f((width / 2) - (bounds4.width / 2), height / (MAX_ITEM_NUM + 1) * 4));
	}

	if (center == false)
	{
		sf::FloatRect bounds = menu_text[0].getLocalBounds();
		menu_text[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM_NUM + 1) * 1));
		menu_text[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM_NUM + 1) * 2));
		menu_text[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM_NUM + 1) * 3));
		menu_text[3].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM_NUM + 1) * 4));
	}
}

void game_menu::moveup()
{
	if (selected_item_index - 1 >= 0)
	{
		menu_text[selected_item_index].setFillColor(sf::Color::White);
		selected_item_index--;
		menu_text[selected_item_index].setFillColor(sf::Color::Magenta);
	}
}

void game_menu::movedown()
{
	if (selected_item_index + 1 < MAX_ITEM_NUM)
	{
		menu_text[selected_item_index].setFillColor(sf::Color::White);
		selected_item_index++;
		menu_text[selected_item_index].setFillColor(sf::Color::Magenta);
	}
}