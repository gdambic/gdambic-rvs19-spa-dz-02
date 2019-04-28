#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

using namespace std;
using namespace sf;
class IgraZivota
{
public:
	IgraZivota(RenderWindow* window);
	void draw(Clock &sat, int x, int y);
	void inicijalizacija();
	void simulacija();
	void set_boja(char &ziv, char &mrtav);
private:
	RenderWindow* window;
	void set_kvadrati();
	void set_rezolucija(int a, int b);
	bool prvi = true;
	void provjera_susjeda(int brojac, int x, int y, int baza);
	RectangleShape zivi_kvadrat;
	RectangleShape mrtvi_kvadrat;
	RectangleShape kvadrat;
	int a, b; //rezolucija
	char ziv, mrtav; //kodovi boje
	
	vector<int> nova_generacija;
	vector<int> stara_generacija;
};

