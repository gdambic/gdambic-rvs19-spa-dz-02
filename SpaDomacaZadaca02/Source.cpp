//#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include <Windows.h>
#include"game_of_life.h"

using namespace std;



int main()
{



	game_of_life the_game;
	bool dalje;

	the_game.generacija01();
	do {


		the_game.iscrtaj();
		the_game.sljedeca_generacija();
		cout << endl;

		cout << "dalje (1/0): ";
		cin >> dalje;
	
	} while (dalje);

	return 0;
}