#include "game_of_life.h"
#include <ctime>
#include <chrono>
#include <array>
using namespace std::chrono;

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
}

void game_of_life::reset()
{
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = slucajna_vrijednost();
		}
	}
}

void game_of_life::ocisti()
{
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = false;
		}
	}
}

void game_of_life::klik(int x, int y)
{

	int i = (y - POMAK - SIZE) / SIZE;
	if (i<0 || i>= REDAKA || y - POMAK - SIZE < 0)
		return odklik();
	int j = (x - SIZE) / SIZE;
	if (j<0 || j>=STUPACA || x - SIZE < 0)
		return odklik();
	
	if (zadnjiklik.first != i || zadnjiklik.second != j) {
		_generacija[i][j] = !_generacija[i][j];
		zadnjiklik.first = i;
		zadnjiklik.second = j;
	}
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
	
	//!!!ovo je bilo PRESPORO pa sam morao napraviti vertex!!!
	/*for (int i = 0; i <= 1; ++i) {
		for (int j = 0; j <= STUPACA+1; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f(j*SIZE, POMAK + SIZE * i * (REDAKA+1)));
			sf::Color boja = sf::Color(0, 0, 255);
			celija.setFillColor(boja);
			window->draw(celija);
		}
	}

	for (int i = 0; i <= 1; ++i) {
		for (int j = 1; j <= REDAKA; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f((STUPACA+1)*i*SIZE, POMAK + SIZE * j));
			sf::Color boja = sf::Color(0, 0, 255);
			celija.setFillColor(boja);
			window->draw(celija);
		}
	}

	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			sf::RectangleShape celija(sf::Vector2f(SIZE, SIZE));
			celija.setPosition(sf::Vector2f(j*SIZE+SIZE, POMAK +SIZE*i+SIZE));
			sf::Color boja = _generacija[i][j] ? sf::Color(255,0,0) : sf::Color(0, 0, 0);
			celija.setFillColor(boja);
			window->draw(celija);
		}
	}*/
	sf::Color boja = sf::Color(0, 0, 255);

	//gornji rub
	DRAWS.emplace_back(sf::Vector2f(0, POMAK), boja);
	DRAWS.emplace_back(sf::Vector2f(0, POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * (STUPACA + 2), POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * (STUPACA + 2), POMAK), boja);

	//donji rub
	DRAWS.emplace_back(sf::Vector2f(0, (REDAKA+1)*SIZE + POMAK), boja);
	DRAWS.emplace_back(sf::Vector2f(0, (REDAKA + 1)*SIZE + POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * (STUPACA + 2), (REDAKA + 1)*SIZE + POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * (STUPACA + 2), (REDAKA + 1)*SIZE + POMAK), boja);

	//lijevi rub
	DRAWS.emplace_back(sf::Vector2f(0, POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(0, POMAK + SIZE + SIZE * REDAKA), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE, POMAK + SIZE + SIZE * REDAKA), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE, POMAK + SIZE), boja);

	//desni rub
	DRAWS.emplace_back(sf::Vector2f(SIZE * STUPACA + SIZE, POMAK + SIZE), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * STUPACA + SIZE, POMAK + SIZE + SIZE * REDAKA), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * STUPACA + SIZE*2, POMAK + SIZE + SIZE * REDAKA), boja);
	DRAWS.emplace_back(sf::Vector2f(SIZE * STUPACA + SIZE*2, POMAK + SIZE), boja);

	boja = sf::Color(255, 0, 0);
	//auto begin = high_resolution_clock::now();
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j) {
			if (!_generacija[i][j])
				continue;
			DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE, POMAK + SIZE * i + SIZE), boja);
			DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE, POMAK + SIZE * i + SIZE * 2), boja);
			DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE * 2, POMAK + SIZE * i + SIZE * 2), boja);
			DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE * 2, POMAK + SIZE * i + SIZE), boja);
		}
	}
	//auto end = high_resolution_clock::now();
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int i = (position.y - POMAK - SIZE) / SIZE;
	int j = (position.x - SIZE) / SIZE;
	if (!(j < 0 || j >= STUPACA) && !(i < 0 || i >= REDAKA) && position.y - POMAK - SIZE> 0 && position.x - SIZE > 0) {
		boja = _generacija[i][j] ? boja = sf::Color(140, 0, 0) : boja = sf::Color(70, 70, 70);

		DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE, POMAK + SIZE * i + SIZE), boja);
		DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE, POMAK + SIZE * i + SIZE * 2), boja);
		DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE * 2, POMAK + SIZE * i + SIZE * 2), boja);
		DRAWS.emplace_back(sf::Vector2f(j*SIZE + SIZE * 2, POMAK + SIZE * i + SIZE), boja);
	}
	
	
	window->draw(&DRAWS[0], DRAWS.size(), sf::Quads);
	
	DRAWS.clear();
	
	//cout << "Traje " << duration_cast<microseconds>(end - begin).count() << " microsekundi. " << endl;
}

void game_of_life::REDAKAup()
{
	++REDAKA;
	_generacija.push_back(vector<bool>(STUPACA));
	_sljedeca_generacija.push_back(vector<bool>(STUPACA));
}

void game_of_life::REDAKAdown()
{
	if (REDAKA > 3) 
		--REDAKA;
	else 
		return;
	_generacija.pop_back();
	_sljedeca_generacija.pop_back();
}

void game_of_life::STUPACAup()
{
	++STUPACA;
	for (int i = 0; i < REDAKA; ++i) {
		_generacija[i].push_back(false);
		_sljedeca_generacija[i].push_back(false);
	}
}

void game_of_life::STUPACAdown()
{
	if (STUPACA > 3)
		--STUPACA;
	else
		return;
	for (int i = 0; i < REDAKA; ++i) {
		_generacija[i].pop_back();
		_sljedeca_generacija[i].pop_back();
	}
}
