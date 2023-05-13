#include "game_of_life.h"

int game_of_life::gen_rnd(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

bool game_of_life::slucajna_vrijednost()
{
    int srand(time(nullptr));
    if (gen_rnd(1, 4) == 1)
    {
        return true;
    }
    return false;
}

bool game_of_life::celija_zauzeta(int i, int j)
{
    if (i < 0 || i >= REDAKA || j < 0 || j >= STUPACA) {
        return false;
    }
    else {
        return _generacija[i][j];
    }
}

game_of_life::game_of_life(RenderWindow* window)
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = slucajna_vrijednost();
        }
    }
    this->window = window;
}

game_of_life::game_of_life()
{
}

void game_of_life::sljedeca_generacija()
{
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            int broj_susjeda = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) {
                        // Skips position for counting nearby cells
                        continue;
                    }
                    if (celija_zauzeta(i + di, j + dj)) {
                        broj_susjeda++;
                    }
                }
            }
            if (_generacija[i][j]) {
                // Cell is alive
                if (broj_susjeda < 2 || broj_susjeda > 3) {
                    // Dies if <2 or >3
                    _sljedeca_generacija[i][j] = false;
                }
                else {
                    // Cells lives
                    _sljedeca_generacija[i][j] = true;
                }
            }
            else {
                // Cell is dead
                if (broj_susjeda == 3) {
                    // Has 3 nearby cells --> revives
                    _sljedeca_generacija[i][j] = true;
                }
                else {
                    // Stays unalive
                    _sljedeca_generacija[i][j] = false;
                }
            }
        }
    }
    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = _sljedeca_generacija[i][j];
        }
    }
}

void game_of_life::iscrtaj()
{
    RectangleShape cell(Vector2f(20.f, 20.f));
    RectangleShape dead(Vector2f(20.f, 20.f));
    
    int x = 0;
    while (x != 50000)
    {
        cell.setFillColor(Color(double(gen_rnd(0, 255)), double(gen_rnd(0, 255)), double(gen_rnd(0, 255)), 200.f));
        x++;
    }
    
    cell.setOutlineColor(Color::Black);

    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            if (_generacija[i][j]) {
//                cout << "*";
                
                cell.setPosition(i * 20, j * 20);
                window->draw(cell);
            }
            else {
 //               cout << ".";
            }
        }
        cout << endl;
    }
}
