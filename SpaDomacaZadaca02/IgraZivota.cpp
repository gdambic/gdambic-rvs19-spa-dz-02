#include "IgraZivota.h"
//#include <iostream> //custom debug
//using namespace std; //custom debug

IgraZivota::IgraZivota(RenderWindow * window)
{
	this->window = window;
}

void IgraZivota::draw(Clock &sat, int x, int y)
{
	srand(time(nullptr));
	set_rezolucija(x, y);
	inicijalizacija();

}

int inicijalni_zivot() {
	int provjera = rand() % (4 - 1 + 1) + 1;
	if (provjera != 4) {
		return 0;
	}
	return 1;
}

void IgraZivota::inicijalizacija()
{
	set_kvadrati();
	int x = 0, y = 0;
	int brojac = 0;
	for (unsigned i = 1; i <= b; i++)	{
		for (unsigned j = 1; j <= a; j++) {
			if (inicijalni_zivot() == 1) {
				//crta zivog
				zivi_kvadrat.setPosition(x, y);
				window->draw(zivi_kvadrat);
				nova_generacija.push_back(1);
			}
			else {
				//crta mrtvog
				mrtvi_kvadrat.setPosition(x, y);
				window->draw(mrtvi_kvadrat);
				nova_generacija.push_back(0);
			}
			x += 10;
			brojac++;
		}
		x = 0;
		y += 10;
	}
	//nova_generacija.shrink_to_fit();
}

void IgraZivota::simulacija()
{
	stara_generacija = nova_generacija;
	int brojac = 0;
	int x = 0, y = 0;
	//gornji lijevi kut
		if (stara_generacija[1] == 1) {
			brojac++;
		}
		if (stara_generacija[a] == 1) {
			brojac++;
		}
		if (stara_generacija[a+1] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, 0);

	x += 10;
	//ostatak prvog reda (osim zadnje celije)
	for (unsigned i = 1; i < a-1; i++) {
		brojac = 0;
		if (stara_generacija[i - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + (a-1)] == 1) {
			brojac++;
		}
		if (stara_generacija[i + a] == 1) {
			brojac++;
		}
		if (stara_generacija[i + (a+1)] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, i);
		x += 10;
	}
	//gornji desni kut
	if (stara_generacija[a-2] == 1) {
		brojac++;
	}
	if (stara_generacija[a*2-2] == 1) {
		brojac++;
	}
	if (stara_generacija[a*2-1] == 1) {
		brojac++;
	}

	provjera_susjeda(brojac, x, y, 79);
	x = 0;
	y += 10;
	//sredina
	int temp = a;
	for (unsigned i = 2; i <= b-1; i++) {
		//prvi s lijeva
		brojac = 0;
		if (stara_generacija[temp - a] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - (a-1)] == 1) {
			brojac++;
		}
		if (stara_generacija[temp +1] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + a] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + (a + 1)] == 1) {
			brojac++;
		}
		provjera_susjeda(brojac, x, y, temp);
		x += 10;
		//sredina sredine
		for (unsigned j = temp + 1; j < temp + a-1; j++) {
			brojac = 0;
			if (stara_generacija[j - 1] == 1) {
				brojac++;
			}
			if (stara_generacija[j + 1] == 1) {
				brojac++;
			}
			if (stara_generacija[j + (a - 1)] == 1) {
				brojac++;
			}
			if (stara_generacija[j + a] == 1) {
				brojac++;
			}
			if (stara_generacija[j + (a + 1)] == 1) {
				brojac++;
			}
			if (stara_generacija[j - (a - 1)] == 1) {
				brojac++;
			}
			if (stara_generacija[j - a] == 1) {
				brojac++;
			}
			if (stara_generacija[j - (a + 1)] == 1) {
				brojac++;
			}

			//cout << i << "," << j << ' '; //custom debug

			provjera_susjeda(brojac, x, y, j);
			x += 10;
		}
		//zadnji s lijeva
		temp += (a-1);
		brojac = 0;
		
		if (stara_generacija[temp - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - a] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - (a + 1)] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + a] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + (a - 1)] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, temp);
		x = 0;
		y += 10;
		temp++;
	}
	//donji lijevi kut
	temp--;
	brojac = 0;
	//cout << "t: " << temp << ' '; //custom debug
	if (stara_generacija[(a*b - a) + 1] == 1) {
		brojac++;
	}
	if (stara_generacija[(a*b -a) - a] == 1) {
		brojac++;
	}
	if (stara_generacija[(a*b - a) - (a-1)] == 1) {
		brojac++;
	}
	provjera_susjeda(brojac, x, y, temp);
	x += 10;
	//cout << "prosao donji lijevi " << endl; //custom debug

	//sredina zadnjeg reda (osim zadnje celije)
	for (unsigned i = ((a*b-a)+1); i < (((a*b - a) + 1)+(a-2)); i++) {
		brojac = 0;
		if (stara_generacija[i - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i - (a - 1)] == 1) {
			brojac++;
		}
		if (stara_generacija[i - a] == 1) {
			brojac++;
		}
		if (stara_generacija[i - (a + 1)] == 1) {
			brojac++;
		}

		//cout << i << ' '; //custom debug

		provjera_susjeda(brojac, x, y, i);
		x += 10;
	}
	//donji desni kut
	if (stara_generacija[a*b-2] == 1) {
		brojac++;
	}
	if (stara_generacija[(a*b-1)-a] == 1) {
		brojac++;
	}
	if (stara_generacija[(a*b-1)-(a+1)] == 1) {
		brojac++;
	}

	provjera_susjeda(brojac, x, y, 79);
	x = 0;
	y += 10;
}

void IgraZivota::set_boja(char &ziv, char &mrtav)
{
	this->ziv = ziv;
	this->mrtav = mrtav;
}

void IgraZivota::set_kvadrati()
{
	switch (ziv) {
	case 'a':
	case 'A':
		zivi_kvadrat.setFillColor(Color::Black);
		break;
	case 'b':
	case 'B':
		zivi_kvadrat.setFillColor(Color::White);
		break;
	case 'c':
	case 'C':
		zivi_kvadrat.setFillColor(Color::Red);
		break;
	case 'd':
	case 'D':
		zivi_kvadrat.setFillColor(Color::Green);
		break;
	case 'e':
	case 'E':
		zivi_kvadrat.setFillColor(Color::Blue);
		break;
	case 'f':
	case 'F':
		zivi_kvadrat.setFillColor(Color::Yellow);
		break;
	case 'g':
	case 'G':
		zivi_kvadrat.setFillColor(Color::Magenta);
		break;
	case 'h':
	case 'H':
		zivi_kvadrat.setFillColor(Color::Cyan);
		break;
	default:
		zivi_kvadrat.setFillColor(Color::White);;
	}
	zivi_kvadrat.setSize(Vector2f(10, 10));

	switch (mrtav) {
	case 'a':
	case 'A':
		mrtvi_kvadrat.setFillColor(Color::Black);
		break;
	case 'b':
	case 'B':
		mrtvi_kvadrat.setFillColor(Color::White);
		break;
	case 'c':
	case 'C':
		mrtvi_kvadrat.setFillColor(Color::Red);
		break;
	case 'd':
	case 'D':
		mrtvi_kvadrat.setFillColor(Color::Green);
		break;
	case 'e':
	case 'E':
		mrtvi_kvadrat.setFillColor(Color::Blue);
		break;
	case 'f':
	case 'F':
		mrtvi_kvadrat.setFillColor(Color::Yellow);
		break;
	case 'g':
	case 'G':
		mrtvi_kvadrat.setFillColor(Color::Magenta);
		break;
	case 'h':
	case 'H':
		mrtvi_kvadrat.setFillColor(Color::Cyan);
		break;
	default:
		zivi_kvadrat.setFillColor(Color::Red);;
	}
	mrtvi_kvadrat.setSize(Vector2f(10, 10));
}

void IgraZivota::set_rezolucija(int a, int b)
{
	this->a = a/10;
	this->b = b/10;
}

void IgraZivota::provjera_susjeda(int brojac, int x, int y, int baza)
{
	if (brojac == 3 && nova_generacija[baza] == 0) {
		nova_generacija[baza] = 1;
		zivi_kvadrat.setPosition(x, y);
		window->draw(zivi_kvadrat);
	}

	else if ((brojac == 2 || brojac == 3) && nova_generacija[baza] == 1) {
		nova_generacija[baza] = 1;
		zivi_kvadrat.setPosition(x, y);
		window->draw(zivi_kvadrat);
	}

	else if ((brojac < 2 || brojac > 3) && nova_generacija[baza] == 1) {
		nova_generacija[baza] = 0;
		mrtvi_kvadrat.setPosition(x, y);
		window->draw(mrtvi_kvadrat);
	}

	else {
		nova_generacija[baza] = 0;
		mrtvi_kvadrat.setPosition(x, y);
		window->draw(mrtvi_kvadrat);
	}
}