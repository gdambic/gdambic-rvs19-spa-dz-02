#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class game_of_life {
private:
	int SIZE = 10;
	int STUPACA=40;
	int REDAKA=20;
	vector<vector<bool>> _generacija{ REDAKA, vector<bool>(STUPACA) };
	vector<vector<bool>> _sljedeca_generacija{ REDAKA, vector<bool>(STUPACA) };
	bool slucajna_vrijednost();
	bool nova_celija(int i, int j);
	int susjedi(int i, int j);

public:
	sf::RenderWindow* window;
	game_of_life(sf::RenderWindow* window);
	void sljedeca_generacija();
	void iscrtaj();
	void SIZEup() { ++SIZE; };
	void SIZEdown() { --SIZE; };

};

#endif
