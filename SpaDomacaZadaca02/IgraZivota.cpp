#include "IgraZivota.h"


IgraZivota::IgraZivota(RenderWindow * window)
{
	this->window = window;
}

void IgraZivota::draw(Clock &sat)
{
	srand(time(nullptr));
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
	for (unsigned i = 1; i <= 60; i++)	{
		for (unsigned j = 1; j <= 80; j++) {
			if (inicijalni_zivot() == 1) {
				//crta zivog
				zivi_kvadrat.setPosition(x, y);
				window->draw(zivi_kvadrat);
				nova_generacija[brojac] = 1;
			}
			else {
				//crta mrtvog
				mrtvi_kvadrat.setPosition(x, y);
				window->draw(mrtvi_kvadrat);
				nova_generacija[brojac] = 0;
			}
			x += 10;
			brojac++;
		}
		x = 0;
		y += 10;
	}
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
		if (stara_generacija[80] == 1) {
			brojac++;
		}
		if (stara_generacija[81] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, 0);

	x += 10;
	//ostatak prvog reda (osim zadnje celije)
	for (unsigned i = 1; i < 79; i++) {
		brojac = 0;
		if (stara_generacija[i - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 79] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 80] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 81] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, i);
		x += 10;
	}
	//gornji desni kut
	if (stara_generacija[78] == 1) {
		brojac++;
	}
	if (stara_generacija[158] == 1) {
		brojac++;
	}
	if (stara_generacija[159] == 1) {
		brojac++;
	}

	provjera_susjeda(brojac, x, y, 79);
	x = 0;
	y += 10;
	//sredina
	int temp = 80;
	for (unsigned i = 2; i <= 59; i++) {
		//prvi s lijeva
		brojac = 0;
		if (stara_generacija[temp - 80] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - 79] == 1) {
			brojac++;
		}
		if (stara_generacija[temp +1] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + 80] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + 81] == 1) {
			brojac++;
		}
		provjera_susjeda(brojac, x, y, temp);
		x += 10;
		//sredina sredine
		for (unsigned j = temp + 1; j < temp + 79; j++) {
			brojac = 0;
			if (stara_generacija[j - 1] == 1) {
				brojac++;
			}
			if (stara_generacija[j + 1] == 1) {
				brojac++;
			}
			if (stara_generacija[j + 79] == 1) {
				brojac++;
			}
			if (stara_generacija[j + 80] == 1) {
				brojac++;
			}
			if (stara_generacija[j + 81] == 1) {
				brojac++;
			}
			if (stara_generacija[j - 79] == 1) {
				brojac++;
			}
			if (stara_generacija[j - 80] == 1) {
				brojac++;
			}
			if (stara_generacija[j - 81] == 1) {
				brojac++;
			}

			provjera_susjeda(brojac, x, y, j);
			x += 10;
		}
		//zadnji s lijeva
		temp += 79;
		brojac = 0;
		
		if (stara_generacija[temp - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - 80] == 1) {
			brojac++;
		}
		if (stara_generacija[temp - 81] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + 80] == 1) {
			brojac++;
		}
		if (stara_generacija[temp + 79] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, temp);
		x = 0;
		y += 10;
		temp++;
	}
	//donji lijevi kut
	brojac = 0;
	if (stara_generacija[4721] == 1) {
		brojac++;
	}
	if (stara_generacija[4720-80] == 1) {
		brojac++;
	}
	if (stara_generacija[4720 - 79] == 1) {
		brojac++;
	}
	provjera_susjeda(brojac, x, y, temp);
	x += 10;

	//sredina zadnjeg reda (osim zadnje celije)
	for (unsigned i = 4721; i < 4721+78; i++) {
		brojac = 0;
		if (stara_generacija[i - 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i + 1] == 1) {
			brojac++;
		}
		if (stara_generacija[i - 79] == 1) {
			brojac++;
		}
		if (stara_generacija[i - 80] == 1) {
			brojac++;
		}
		if (stara_generacija[i - 81] == 1) {
			brojac++;
		}

		provjera_susjeda(brojac, x, y, i);
		x += 10;
	}
	//donji desni kut
	if (stara_generacija[4799 - 1] == 1) {
		brojac++;
	}
	if (stara_generacija[4799 - 80] == 1) {
		brojac++;
	}
	if (stara_generacija[4799 - 81] == 1) {
		brojac++;
	}

	provjera_susjeda(brojac, x, y, 79);
	x = 0;
	y += 10;
}

void IgraZivota::set_kvadrati()
{
	zivi_kvadrat.setFillColor(Color::White);
	zivi_kvadrat.setSize(Vector2f(10, 10));

	mrtvi_kvadrat.setFillColor(Color::Black);
	mrtvi_kvadrat.setSize(Vector2f(10, 10));
}

void IgraZivota::provjera_susjeda(int brojac, int x, int y, int baza)
{
	if (brojac == 3 && nova_generacija[baza] == 0) {
		nova_generacija[baza] = 1;
		zivi_kvadrat.setPosition(x, y);
		window->draw(zivi_kvadrat);
	}

	//nepotrebno
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
}