#include <SFML/Graphics.hpp>
#include <iostream>
#include "IgraZivota.h"

void rezolucija(int &xs, int &y);
void boja(char &ziv, char &mrtav);
void ispisi_naslov();

int main()
{
	ispisi_naslov();
	int x, y;
	char ziv, mrtav;
	try { rezolucija(x, y); } catch (const exception& err) { cout << err.what() << endl; }
	boja(ziv, mrtav);

	bool prvi = true;
	sf::RenderWindow window(sf::VideoMode(x, y), "Hello, SFML world!");
	window.setFramerateLimit(60);
	IgraZivota igra(&window);
	igra.set_boja(ziv, mrtav);
	Clock sat;
	igra.draw(sat, x, y);
	window.display();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sat.getElapsedTime() >= seconds(2)) {
			window.clear();
			igra.simulacija();
			window.display();
			sat.restart();
		}
	}
	return 0;
}

void rezolucija(int &x, int &y) {
	char odabir;
		cout << "Odaberite jednu od ponudjenih rezolucija" << endl
		<< "----------------------------------------" << endl
		<< "a) 800x600" << endl
		<< "b) 800x800" << endl
		<< "c) 1280x720" << endl
		<< "d) 1920x1080" << endl;
	do{
		cout << "Unesite slovo ispred zeljene rezolucije: ";
		cin >> odabir;

		if (odabir != 'a' && odabir != 'b' && odabir != 'c' && odabir != 'd' &&
			odabir != 'A' && odabir != 'B' && odabir != 'C' && odabir != 'D') {
			cout << "Pogresan unos!" << endl;
		}


	} while (odabir != 'a' && odabir != 'b' && odabir != 'c' && odabir != 'd' &&
			 odabir != 'A' && odabir != 'B' && odabir != 'C' && odabir != 'D');
	

	switch (odabir) {
	case 'a':
	case 'A':
		x = 800;
		y = 600;
		break;
	case 'b':
	case 'B':
		x = 800;
		y = 800;
		break;
	case 'c':
	case 'C':
		x = 1280;
		y = 720;
		break;
	case 'd':
	case 'D':
		x = 1920;
		y = 1080;
		break;
	default:
		throw exception("Greska pri odabiru rezolucije");
	}
}

void boja(char &ziv, char &mrtav) {
	//ZIVA CELIJA
	system("cls");
	ispisi_naslov();
	cout << "Odaberite boju zive celije" << endl
		<< "------------------------" << endl
		<< "a) Crna" << endl
		<< "b) Bijela" << endl
		<< "c) Crvena" << endl
		<< "d) Zelena" << endl
		<< "e) Plava" << endl
		<< "f) Zuta" << endl
		<< "g) Ruzicasta" << endl
		<< "h) Modra" << endl;

	do {
		cout << "Unesite slovo ispred zeljene boje zive celije: ";
		cin >> ziv;
			if (ziv != 'a' && ziv != 'b' && ziv != 'c' && ziv != 'd' &&
				ziv != 'A' && ziv != 'B' && ziv != 'C' && ziv != 'D' &&
				ziv != 'e' && ziv != 'f' && ziv != 'g' && ziv != 'h' &&
				ziv != 'E' && ziv != 'F' && ziv != 'G' && ziv != 'H') {
				cout << "Pogresan unos!" << endl;
			}

	} while (ziv != 'a' && ziv != 'b' && ziv != 'c' && ziv != 'd' &&
		ziv != 'A' && ziv != 'B' && ziv != 'C' && ziv != 'D' &&
		ziv != 'e' && ziv != 'f' && ziv != 'g' && ziv != 'h' &&
		ziv != 'E' && ziv != 'F' && ziv != 'G' && ziv != 'H');

	//MRTVA CELIJA
	system("cls");
	ispisi_naslov();
	cout << "Odaberite boju mrtve celije" << endl
		<< "------------------------" << endl
		<< "a) Crna" << endl
		<< "b) Bijela" << endl
		<< "c) Crvena" << endl
		<< "d) Zelena" << endl
		<< "e) Plava" << endl
		<< "f) Zuta" << endl
		<< "g) Ruzicasta" << endl
		<< "h) Modra" << endl;

	do {
		cout << "Unesite slovo ispred zeljene boje zive celije: ";
		cin >> mrtav;
		if (mrtav != 'a' && mrtav != 'b' && mrtav != 'c' && mrtav != 'd' &&
			mrtav != 'A' && mrtav != 'B' && mrtav != 'C' && mrtav != 'D' &&
			mrtav != 'e' && mrtav != 'f' && mrtav != 'g' && mrtav != 'h' &&
			mrtav != 'E' && mrtav != 'F' && mrtav != 'G' && mrtav != 'H') {
			cout << "Pogresan unos!" << endl;
		}
		if (mrtav == ziv) {
			cout << "Boja zivih i boja mrtvih celija ne smiju biti jednake." << endl;
		}

	} while ((mrtav != 'a' && mrtav != 'b' && mrtav != 'c' && mrtav != 'd' &&
		mrtav != 'A' && mrtav != 'B' && mrtav != 'C' && mrtav != 'D' &&
		mrtav != 'e' && mrtav != 'f' && mrtav != 'g' && mrtav != 'h' &&
		mrtav != 'E' && mrtav != 'F' && mrtav != 'G' && mrtav != 'H') || (mrtav == ziv));

}

void ispisi_naslov() {
	cout << " I G R A   Z I V O T A   S I M U L A T O R" << endl
		<< "------------------------------------------" << endl;
}