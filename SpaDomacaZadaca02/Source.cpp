/*
©Dominik Despot
CC BY-NC-SA
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Menu.h"
#include "jcgol.h"
using namespace std;
using namespace sf;
int main(void){

	sf::err().rdbuf(NULL);

	RenderWindow window(sf::VideoMode(1920, 1080), "John Conway's game of life © Dominik Despot");

	sf::Image icon;
	icon.loadFromFile ("Resources\\icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(60);

	Music menu_music;
	menu_music.setLoop(true);
	if (!menu_music.openFromFile("Resources\\menu_music.ogg"))
		return 404;
	menu_music.play();

	Menu menu;
	jcgol game;

	switch (menu.display(window)) {
	case 1:game.display(window); break;
	case 2:game.display_random(window); break;
	default:break;
	}

	return 0;
}