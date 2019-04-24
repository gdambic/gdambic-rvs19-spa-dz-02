#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

using namespace std;
using namespace sf;
class IgraZivota
{
public:
	IgraZivota(RenderWindow* window);
	void draw(Clock &sat);
	void inicijalizacija();
	void simulacija();
private:
	RenderWindow* window;
	void set_kvadrati();
	bool prvi = true;
	void provjera_susjeda(int brojac, int x, int y, int baza);
	RectangleShape zivi_kvadrat;
	RectangleShape mrtvi_kvadrat;
	RectangleShape kvadrat;
	
	array<int, 4800> nova_generacija;
	array<int, 4800> stara_generacija;
};

