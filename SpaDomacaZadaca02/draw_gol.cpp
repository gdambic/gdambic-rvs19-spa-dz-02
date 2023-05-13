#include "draw_gol.h"
#include <ctime>
#include <iostream>

game_of_life::game_of_life() {
    srand(time(nullptr));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {   // generiram random broj između 1 i 4, ako je jednak 1 celija je ziva = 25% sanse
            (gen_rnd() == 1) ? (_curr_gen[i][j] = true) : (_curr_gen[i][j] = false);

            _next_gen[i][j] = false;
        }
    }
}

draw_gol::draw_gol(sf::RenderWindow* window)
{
	this->window = window;
    this->g = new game_of_life();
}

void draw_gol::mouse_clicked_left(sf::Vector2i& mousePos) {
    g->kill_cells(mousePos);
}
void draw_gol::mouse_clicked_right(sf::Vector2i& mousePos) {
    g->populate_cells(mousePos);
}

int draw_gol::need_generation_count() {
    return g->get_generation_count();
}

void draw_gol::watch_gol()
{
    srand(time(nullptr));
    
    std::cout << "Generacija: " << g->get_generation_count() << endl;
    sf::Color alive_color(gen_rnd(0, 255), gen_rnd(0, 255), gen_rnd(0, 255));
    sf::Color dead_color(0, 0, 0);
    sf::Color rand_color(gen_rnd(0, 255), gen_rnd(0, 255), gen_rnd(0, 255));
    

    sf::RectangleShape cell_alive(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));
    cell_alive.setOutlineThickness(1);
    cell_alive.setOutlineColor(sf::Color::Yellow);
    cell_alive.setFillColor(alive_color);

    sf::RectangleShape cell_dead(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));
    //cell_dead.setFillColor(dead_color);
    if (g->get_generation_count() % 15 == 0)
    {
        cell_dead.setFillColor(rand_color);
    }
    else
    {
        cell_dead.setFillColor(dead_color);
    }

    if (g->get_generation_count() % 10 == 0)
    {
        cell_alive.setOutlineThickness(5);
        cell_alive.setOutlineColor(sf::Color::Green);
        cell_dead.setOutlineThickness(3);
        cell_dead.setOutlineColor(sf::Color::Blue);
    }
    

    window->setActive(true);
    window->clear(dead_color);
    for (int i = 0; i < g->get_rows(); i++)
    {
        for (int j = 0; j < g->get_columns(); j++)
        {
            if (g->get_curr_gen(i, j))
            {
                cell_alive.setPosition(i * g->get_cell_size(), j * g->get_cell_size());
                window->draw(cell_alive);
            }
            else
            {
                cell_dead.setPosition(i * g->get_cell_size(), j * g->get_cell_size());
                window->draw(cell_dead);
            }
            
        }
    }
    window->setActive(false);
    
    g->next_gen();
}

void game_of_life::copy_curr_to_next() {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            _curr_gen[i][j] = _next_gen[i][j];
        }
    }
}

void game_of_life::kill_cells(sf::Vector2i& mousePos) {

    int row = mousePos.x / 10.0f;
    int col = mousePos.y / 10.0f;
    std::cout << "Kill called!" << endl;
    // kill the clicked cell and its 20 surrounding cells
    for (int i = row - 4; i <= row + 4; i++) {
        for (int j = col - 4; j <= col + 4; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < columns) {
                _next_gen[i][j] = false;
                
            }
        }
    }
    copy_curr_to_next();
}

void game_of_life::populate_cells(sf::Vector2i& mousePos) {

    int row = mousePos.x / 10.0f;
    int col = mousePos.y / 10.0f;
    std::cout << "Populate called!" << endl;
    // populate the clicked cell and its 20 surrounding cells
    for (int i = row - 4; i <= row + 4; i++) {
        for (int j = col - 4; j <= col + 4; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < columns) {
                _next_gen[i][j] = true;

            }
        }
    }
    copy_curr_to_next();
}



void game_of_life::next_gen()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int neighbour_count = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0)
                        continue;

                    int ni = (i + di + rows) % rows;
                    int nj = (j + dj + columns) % columns;

                    neighbour_count += _curr_gen[ni][nj];
                }
            }
            if (_curr_gen[i][j])
                _next_gen[i][j] = (neighbour_count == 2 || neighbour_count == 3);
            else
                _next_gen[i][j] = (neighbour_count == 3);
        }
    }
    copy_curr_to_next();
    set_generation_count(get_generation_count() + 1);
}


bool game_of_life::get_curr_gen(int i, int j) {
    return _curr_gen[i][j];
}

int game_of_life::gen_rnd() { // Generiranje broja između 1 i 4
    return rand() % 4 + 1;
}

int draw_gol::gen_rnd(int min, int max) { // For colors rgb values
    return rand() % (max - min + 1) + min;
}

int game_of_life::get_generation_count() {
    return generation_counter;
}

void game_of_life::set_generation_count(int n) {
    this->generation_counter = n;
}

float game_of_life::get_cell_size() {
    return cell_size;
}

int game_of_life::get_rows() {
    return rows;
}

int game_of_life::get_columns() {
    return columns;
}