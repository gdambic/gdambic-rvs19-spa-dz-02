#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <sstream>

using namespace std;

class Small_Screen
{
public:
	Small_Screen(sf::RenderWindow* window);//konstruktor
	void set_cellposition();//Naci njihove pozicije
	void set_cell_size();//stavljanje velicine kucice
	void set_cell();//provjera koliko cega staviti da se pali samo ako je svaki member check_cell-a jednak true, inace ne pali, na kraju firstTime-a staviti firstime = false
	void set_cells();//staviti one sve uvjete i crtati 
	void set_playerposition();//staviti poziciju igraca
	void set_player();
	void set_positiontrack();
	void draw();//crtanje

private:
	int place;
	sf::RenderWindow* Window;
	bool prev_cells[8][4];//jesu li u prosloj bili mrtvi ili zivi
	bool cells[8][4];//jesu li sada mrtvi ili zivi
	bool check_cell[8][4];//provjera je li zastitar prosao tu celiju ili nije
	bool FirstTime;//provjera je li ovo prva generacija zbog random generiranja zivota
	sf::RectangleShape track;
	sf::Vector2f track_position[4];
	sf::Vector2f cells_position[8][4];// pozicija celija zapisanih
	sf::RectangleShape dead;
	sf::RectangleShape live;
	sf::RectangleShape guardian;
	sf::Vector2f players_position[4];//pozicija cuvara
	sf::Vector2f player_size;
	sf::Vector2f prisoner_position[8][4];//pozicija zatvorenika,vjv cu koristii ruke i noge od cuvara za kreiranje njega
	sf::Vector2f cell_size;
};

