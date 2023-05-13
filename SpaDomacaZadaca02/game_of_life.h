#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 54;
	static const unsigned int REDAKA = 96;
	bool _generacija[REDAKA][STUPACA];
	bool _sljedeca_generacija[REDAKA][STUPACA];
	int gen_rnd(int min, int max);
	bool slucajna_vrijednost();
	bool celija_zauzeta(int i, int j);
	RenderWindow* window;

public:
	game_of_life(RenderWindow* window);
	game_of_life();
	void sljedeca_generacija();
	void iscrtaj();
};

#endif
