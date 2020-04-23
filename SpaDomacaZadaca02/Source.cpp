#include "Load.h"
using namespace std;

bool random(unsigned int chance) {
	bool alive;
	alive = ((rand() % 100) < chance);
	return alive;
}

Cell** reservation(unsigned int x, unsigned int y) {

	Cell** theCells = new Cell * [y];
	for (unsigned int i = 0; i < y; i++)
	{
		theCells[i] = new Cell[x];
	}

	return theCells;
}

void creation(Cell** theCells, unsigned int x, unsigned int y, unsigned int chance) {

	for (unsigned int i = 0; i < y; i++)
	{
		for (unsigned int j = 0; j < x; j++)
		{
			theCells[i][j].alive = random(chance);
		}
	}

}

void checkEvent(sf::Window* window,int &delay, bool &paused) {
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				delay += 50;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				delay -= 50;
				if (delay < 0)
				{
					delay = 0;
				}
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				paused = true;
			}
			else if (event.key.code == sf::Keyboard::O)
			{
				paused = false;
			}
		}
	}
}

void firstFrameFix(Cell** theCells, int x, int y, sf::RenderWindow* window ) {

	window->clear(sf::Color(0, 0, 0));
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{

			sf::RectangleShape cell(sf::Vector2f(10, 10));
			cell.setPosition(1 + 11 * j, 1 + 11 * i);
			if (theCells[i][j].alive)
			{
				cell.setFillColor(sf::Color(141, 252, 252));
			}
			else
			{
				cell.setFillColor(sf::Color(46, 46, 46));
			}
			window->draw(cell);
		}
	}
	window->display();
	//auto start = chrono::steady_clock::now();
	//auto end = chrono::steady_clock::now();
	//while (!((chrono::duration_cast<chrono::milliseconds>(end - start)) > chrono::milliseconds(2000)))
	//{
	//	end = chrono::steady_clock::now();
	//}
	this_thread::sleep_for(chrono::seconds(2));
}

void info() {

	cout << "U can change the delay between simulations with arrow key UP (longer delay) and arrow key down (smaller delay)" << endl <<
		"to pause the game press P and to continue press O" << endl;

}

int main()
{
	srand(time(NULL));
	cout << "How big should the gameboard be?" << endl << "Width: ";
	unsigned int x;
	cin >> x;
	cout << "Height: ";
	unsigned int y;
	cin >> y;
	system("cls");
	cout << "How much % of the cells are alive? (1-100)";
	unsigned int chance;
	cin >> chance;

	system("cls");
	
	Cell** theCells = reservation(x, y);

	creation(theCells, x, y, chance);

	// Testing

	//for (int i = 0; i < y; i++)
	//{
	//	for (int j = 0; j < x; j++)
	//	{
	//		if (theCells[i][j].alive)
	//		{
	//			cout << "*";
	//		}
	//		else
	//		{
	//			cout << "_";
	//		}
	//	}
	//	cout << endl;
	//}

	Game game(theCells);

	// Testing

	//while (true)
	//{
	//	game.DeadOrAlive(x, y);
	//	for (int i = 0; i < y; i++)
	//	{
	//		for (int j = 0; j < x; j++)
	//		{
	//			if (theCells[i][j].alive)
	//			{
	//				cout << "*";
	//			}
	//			else
	//			{
	//				cout << "_";
	//			}
	//		}
	//		cout << endl;
	//	}
	//	this_thread::sleep_for(chrono::seconds(0));
	//	system("cls");
	//}


	sf::RenderWindow window(sf::VideoMode(1 + 11*x,1 + 11 * y), "Hello, SFML world!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	game.loadRender(&window);

	info();

	firstFrameFix(theCells, x, y, &window);  // I had a problem with rendering the first frame. I found it after i tried with a 100% chance to spawn alive
											// I don't know how to fix it my function just doesn't want to show the first frame
	game.DeadOrAlive(x, y);

	bool paused = false;

	int delay = 2000;

	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();

	while (window.isOpen())
	{
		checkEvent(&window, delay, paused);
		if (!paused)
		{
			if ((chrono::duration_cast<chrono::milliseconds>(end - start)) > chrono::milliseconds(delay))
			{
				start = chrono::steady_clock::now();
				game.DeadOrAlive(x, y);
			}
		}
		window.clear(sf::Color(0, 0, 0));
		game.render();
		window.display();
		end = chrono::steady_clock::now();
	}

	return 0;
}