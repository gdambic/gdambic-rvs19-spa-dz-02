
#include "GameOfLife.h"
#include <iostream>

using namespace std;



void GameOfLife::start()
{
	char jos = 0;
	this->cRandom();

	do {

		this->prikaz();
		this->sljedecaPloca();
		this->kopiraj();
		cout << "Hoces li jos (d/n): ";
		cin >> jos;
	} while (jos == 'd');
}

void GameOfLife::ploca()
{
	this->trenutna[0][0] = '-';
	this->sljedeca[0][0] = '-';
}



void GameOfLife::cRandom()
{

	for (int i = 0; i < this->ROWS; ++i)
	{
		for (int l = 0; l < this->COLUMS; ++l)
		{
			this->trenutna[i][l] = '-';
		}
	}

	for (int i = 0; i < this->ROWS; i += 2)
	{
		for (int l = 0; l < this->COLUMS; l++)
		{
			if (this->randumO(4, 1) == 4) {
				this->trenutna[i][l] = '*';
			}
		}
	}
}

void GameOfLife::prikaz()

//crtamo plocu
{

	for (int i = 0; i < this->ROWS; i++)
	{
		for (int l = 0; l < this->COLUMS; l++)
		{
			if (this->trenutna[i][l] != '*')
				this->trenutna[i][l] = '-';

			cout << this->trenutna[i][l];

		}
		cout << endl;
	}
}

void GameOfLife::sljedecaPloca()
{
	int susjedi;

	for (int i = 0; i < this->ROWS; i++)
	{
		for (int l = 0; l < this->COLUMS; l++)
		{
			susjedi = this->provjerisusjeda(i, l);
			if (susjedi < 2)
				this->sljedeca[i][l] = '-';
			else if (susjedi > 3)
				this->sljedeca[i][l] = '-';
			else if (susjedi == 3)
				this->sljedeca[i][l] = '*';
			else if (this->trenutna[i][l] == '*' && susjedi == 2)
				this->sljedeca[i][l] = '*';
			else
				sljedeca[i][l] = '-';
		}

	}
}

void GameOfLife::kopiraj()
{
	for (int i = 0; i < this->ROWS; i++)
	{
		for (int l = 0; l < this->COLUMS; l++)
		{
			this->trenutna[i][l] = this->sljedeca[i][l];
		}
	}
}

int GameOfLife::provjerisusjeda(int red, int colum)
{
	int susjed = 0;

	if (this->trenutna[red - 1][colum - 1] == '*')
		++susjed;
	if (this->trenutna[red][colum - 1] == '*')
		++susjed;
	if (this->trenutna[red - 1][colum] == '*')
		++susjed;
	if (this->trenutna[red - 1][colum + 1] == '*')
		++susjed;
	if (this->trenutna[red + 1][colum - 1] == '*')
		++susjed;
	if (this->trenutna[red + 1][colum] == '*')
		++susjed;
	if (this->trenutna[red][colum + 1] == '*')
		++susjed;
	if (this->trenutna[red + 1][colum + 1] == '*')
		++susjed;

	return susjed;
}

int GameOfLife::randumO(int max, int min)
{

	return rand() % (max - min + 1) + min;
}



