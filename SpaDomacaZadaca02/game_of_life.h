#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 40;
	static const unsigned int REDAKA = 20;
	
	//bool _generacija[REDAKA][STUPACA];
	//bool _sljedeca_generacija[REDAKA][STUPACA];
	//bool slucajna_vrijednost();
	//bool celija_zauzeta(int i, int j);
	int gen01[REDAKA][STUPACA];


	
	

public:
	game_of_life();
	void generacija01();
	void copy(int gen01[REDAKA][STUPACA], int temp[20][40]);
	void sljedeca_generacija();
	void iscrtaj();

};

#endif
