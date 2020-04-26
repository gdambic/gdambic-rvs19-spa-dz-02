#include "Gofl.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Gofl::Gofl(sf::RenderWindow* window)
{
	this->window = window;
}

void Gofl::draw()
{
	pickColor();
	text();
	drawBoard();
	Time counter = frameClock.getElapsedTime();
	Time manage = seconds(0.10f);
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		stop += manage;
		setTime();
	}if (Keyboard::isKeyPressed(Keyboard::Down)) {
		stop -= manage;
		setTime();
	}
	if (counter >= stop) {
		change();
		frameClock.restart();
	}

}

void Gofl::setTime()
{
	if (stop <= seconds(0.00f)) {
		stop = seconds(0.00f);
	}if (stop >= seconds(5.00f)) {
		stop = seconds(5.00f);
	}
}

void Gofl::text()
{
	int counter = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (color[i][j] == 0) {
				counter++;
			}
		}
	}

	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "Upisati neki font ";
	}
	else {
		string help = "Zive celije: " + to_string(counter);
		string help2 = "Brzina: " + to_string(stop.asSeconds());
		Text text;
		text.setFont(font);
		text.setPosition(150, 0);
		text.setString(help);
		window->draw(text);
		Text text2;
		text.setFont(font);
		text.setPosition(500, 0);
		text.setString(help2);
		window->draw(text);
	}
}

void Gofl::pickColor()
{
	if (passed) {
		srand(time(nullptr));
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 40; j++) {
				color[i][j] = (rand() % 4);
			}
		}
		passed = false;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 40; j++) {
				if (color[i][j] > 1) {
					color[i][j] = 1;
				}
			}
		}
	}
}

void Gofl::change()
{
	int colorhelp[40][40];
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			colorhelp[i][j] = color[i][j];
		}
	}

	int counter = 0;
	int help1, help2;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {

			help1 = i;
			help2 = j;

			if (help1 - 1 >= 0) {
				help1--;
				//- +/-
				if (colorhelp[help1][help2] == 0) {
					counter++;
				}
				if (help2 - 1 >= 0) {
					help2--;
					//- -
					if (colorhelp[help1][help2] == 0) {
						counter++;
					}
					help2 = j;
				}
				if (help2 + 1 < 40) {
					help2++;
					//- +
					if (colorhelp[help1][help2] == 0) {
						counter++;
					}
					help2 = j;
				}
				help1 = i;
			}

			if (help2 - 1 >= 0) {
				help2--;
				//+/- -
				if (colorhelp[help1][help2] == 0) {
					counter++;
				}
				help2 = j;
			}
			if (help2 + 1 < 40) {
				help2++;
				//+/- +
				if (colorhelp[help1][help2] == 0) {
					counter++;
				}
				help2 = j;
			}

			if (help1 + 1 < 40) {
				help1++;
				//+ +/-
				if (colorhelp[help1][help2] == 0) {
					counter++;
				}
				if (help2 - 1 >= 0) {
					help2--;
					//+ -
					if (colorhelp[help1][help2] == 0) {
						counter++;
					}
					help2 = j;
				}
				if (help2 + 1 < 40) {
					help2++;
					//+ +
					if (colorhelp[help1][help2] == 0) {
						counter++;
					}
					help2 = j;
				}
				help1 = i;
			}


			//Pretvaranje zivih celija u mrtve
			if (counter < 2) {
				if (color[i][j] == 0) {
					color[i][j] = 1;
				}
			}
			else if (counter == 2) {
				if (color[i][j] == 0) {
					color[i][j] = 0;
				}
			}
			else if (counter == 3) {
				if (color[i][j] == 1) {
					color[i][j] = 0;
				}
			}
			else if (counter > 3) {
				if (color[i][j] == 0) {
					color[i][j] = 1;
				}
			}
			counter = 0;
		}
	}
}

void Gofl::drawBoard()
{
	float row = 50;
	float column = 50;
	pickColor();
	RectangleShape rectangle[40][40];
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			rectangle[i][j].setOutlineThickness(3);
			rectangle[i][j].setOutlineColor(Color(600, 0, 0));
			rectangle[i][j].setSize(Vector2f(20, 20));
			rectangle[i][j].setPosition(row, column);
			if (color[i][j] == 0) {
				rectangle[i][j].setFillColor(Color(0, 0, 0));
			}
			else {
				rectangle[i][j].setFillColor(Color(255, 255, 255));
			}
			window->draw(rectangle[i][j]);
			row += 20;
		}

		row = 50;
		column += 20;
	}
}
