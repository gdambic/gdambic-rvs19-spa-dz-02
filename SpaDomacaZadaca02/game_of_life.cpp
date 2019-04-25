#include "game_of_life.h"
#include <ctime>
bool game_of_life::slucajna_vrijednost()
{
	return rand() % 4 == 0;
}

bool game_of_life::nova_celija(int i, int j)
{
	int susjedi = this->susjedi(i, j);
	return susjedi == 3 ? true : susjedi == 2 ? _generacija[i][j] : false;
}

int game_of_life::susjedi(int i, int j)
{
	int susjedi = 0;
	for (int ii = -1; ii <= 1; ii++) {
		for (int jj = -1; jj <= 1; jj++) {
			if ((ii != 0 or jj != 0) && ((i + ii >= 0 && i + ii < REDAKA) && (j + jj >= 0 && j + jj < STUPACA))) {
				susjedi += _generacija[i + ii][j + jj] ? 1 : 0;
				//cout << _generacija[i + ii][j + jj] << " ";
			}

		}
	}
	return susjedi;
}

game_of_life::game_of_life(sf::RenderWindow* window)
{
	this->window = window;
	srand(time(nullptr));
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = slucajna_vrijednost();
		}
	}
	//cout << susjedi(19, 39) << endl;
	//cout << nova_celija(1, 1) << endl;
}

void game_of_life::sljedeca_generacija()
{
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			_sljedeca_generacija[i][j] = nova_celija(i, j);
		}
	}

	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = _sljedeca_generacija[i][j];
		}
	}
}

void game_of_life::iscrtaj()
{
	system("cls");

	for (int i = 0; i <= 1; ++i) {
		for (int j = 0; j <= STUPACA+1; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f(j*SIZE, 30 + SIZE * i * (REDAKA+1)));
			sf::Color boja = sf::Color(0, 0, 255);
			celija.setFillColor(boja);
			window->draw(celija);
		}
	}

	for (int i = 0; i <= 1; ++i) {
		for (int j = 1; j <= REDAKA; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f((STUPACA+1)*i*SIZE, 30 + SIZE * j));
			sf::Color boja = sf::Color(0, 0, 255);
			celija.setFillColor(boja);
			window->draw(celija);
		}
	}

	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f(j*SIZE+SIZE, 30+SIZE*i+SIZE));
			sf::Color boja = _generacija[i][j] ? sf::Color(255,0,0) : sf::Color(0, 0, 0);
			celija.setFillColor(boja);
			window->draw(celija);
			//cout << (_generacija[i][j] ? '*' : '.');
			
		}
		//cout << endl;
	}


}
