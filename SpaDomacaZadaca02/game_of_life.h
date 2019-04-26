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
	sf::RenderWindow* window;
	const int POMAK = 32;
	int SIZE = 10;
	int STUPACA=40;
	int REDAKA=20;
	pair<int,int> zadnjiklik;
	vector<vector<bool>> _generacija{ REDAKA, vector<bool>(STUPACA) };
	vector<vector<bool>> _sljedeca_generacija{ REDAKA, vector<bool>(STUPACA) };
	bool slucajna_vrijednost();
	bool nova_celija(int i, int j);
	int susjedi(int i, int j);
	vector<sf::Vertex> DRAWS;
public:
	game_of_life(sf::RenderWindow* window);
	void reset();
	void ocisti();
	void klik(int x, int y);
	void odklik() {zadnjiklik.first = -1; zadnjiklik.second = -1;}
	void sljedeca_generacija();
	void iscrtaj();
	void SIZEup() { ++SIZE; };
	void SIZEdown() {SIZE==1 ? SIZE=1 : --SIZE; };
	void REDAKAup();
	void REDAKAdown();
	void STUPACAup();
	void STUPACAdown();
};

#endif
