#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
/*to begin the program you need to click on sfml console and draw some shape after that press space you can also stop game by pressing on space and draw another 
shape than press space to continue*/


int main(int argc, char* argv[]) {
	Game gameoflife;
	gameoflife.run();
	return 0;
}
