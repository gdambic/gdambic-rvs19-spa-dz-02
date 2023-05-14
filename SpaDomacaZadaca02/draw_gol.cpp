#include "draw_gol.h"


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

draw_gol::draw_gol(sf::RenderWindow* window, std::string cwd)
{
	this->window = window;
    this->g = new game_of_life();
    this->cwd = cwd;
    init_cat();
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

void draw_gol::init_cat() {
    //if you slap it 5 times it scratches the whole screen
    //find sounds
    this->c = new cat();
    c->catFalling = new sf::RectangleShape(sf::Vector2f(600, 600)); // 600, 600
    c->catFallingTexture = new sf::Texture();
    c->scratches = new sf::RectangleShape(sf::Vector2f(200, 200));
    c->scratchesTexture = new sf::Texture();
    c->curious_1 = new sf::RectangleShape(sf::Vector2f(600, 600));
    c->curious_1Texture = new sf::Texture();
    c->streach_2 = new sf::RectangleShape(sf::Vector2f(600, 600));
    c->streach_2Texture = new sf::Texture();
    c->boom1 = new sf::RectangleShape(sf::Vector2f(200, 200));
    c->boom1Texture = new sf::Texture();
    c->boom2 = new sf::RectangleShape(sf::Vector2f(200, 200));
    c->boom2Texture = new sf::Texture();
    c->paw_prints = new sf::RectangleShape(sf::Vector2f(600, 600));
    c->paw_printsTexture = new sf::Texture();
    

    string cat_falling_texture_path = cwd + "/Pictures/cat_falling.png";
    if (!c->catFallingTexture->loadFromFile(cat_falling_texture_path))
    {
        cout << "Can't the cat" << endl;
    }
    
    c->catFalling->setTexture(c->catFallingTexture);
    c->catFalling->setPosition(-120, -150);

    string scratches_texture_path = cwd + "/Pictures/scratches.png";
    if (!c->scratchesTexture->loadFromFile(scratches_texture_path))
    {
        cout << "404 scratches" << endl;
    }

    c->scratches->setTexture(c->scratchesTexture);
    c->scratches->setPosition(200, 200);

    string curious1_texture_path = cwd + "/Pictures/curious_1.png";
    if (!c->curious_1Texture->loadFromFile(curious1_texture_path))
    {
        cout << "404 curious_1" << endl;
    }

    c->curious_1->setTexture(c->curious_1Texture);
    c->curious_1->setPosition(0, 500);

    string streach2_texture_path = cwd + "/Pictures/streach_2.png";
    if (!c->streach_2Texture->loadFromFile(streach2_texture_path))
    {
        cout << "404 curious_1" << endl;
    }

    c->streach_2->setTexture(c->streach_2Texture);
    c->streach_2->setPosition(0, 500);

    string boom1_texture_path = cwd + "/Pictures/boom1.png";
    if (!c->boom1Texture->loadFromFile(boom1_texture_path))
    {
        cout << "404 boom1" << endl;
    }

    c->boom1->setTexture(c->boom1Texture);
    c->boom1->setPosition(950, 530);

    string boom2_texture_path = cwd + "/Pictures/boom2.png";
    if (!c->boom2Texture->loadFromFile(boom2_texture_path))
    {
        cout << "404 boom2" << endl;
    }

    c->boom2->setTexture(c->boom2Texture);
    c->boom2->setPosition(950, 530);

    string paw_prints_texture_path = cwd + "/Pictures/paw_prints.png";
    if (!c->paw_printsTexture->loadFromFile(paw_prints_texture_path))
    {
        cout << "404 paw_prints" << endl;
    }

    c->paw_prints->setTexture(c->paw_printsTexture);
    c->paw_prints->setPosition(950, 530);

}

void draw_gol::cat_falling() {
    if (g->get_generation_count() > 20)
    {
        int newPosX = -120;
        int newPosY = -150 + g->get_generation_count() * 15;
        c->catFalling->setPosition(newPosX, newPosY);
    }
    
    window->setActive(true);
    window->draw(*c->catFalling);
    window->setActive(false);
}

void draw_gol::scratching() {
    window->setActive(true);
    window->draw(*c->scratches);
    window->setActive(false);
}

void draw_gol::curious_streach() {

    if (g->get_generation_count() >= 60 && g->get_generation_count() <= 75)
    {
        window->setActive(true);
        window->draw(*c->curious_1);
        window->setActive(false);
    }
    else if (g->get_generation_count() >= 75 && g->get_generation_count() <= 90)
    {
        window->setActive(true);
        window->draw(*c->streach_2);
        window->setActive(false);
    }

}

void draw_gol::boom() {

    if (g->get_generation_count() >= 90 && g->get_generation_count() <= 100)
    {
        if (g->get_generation_count() >= 90 && g->get_generation_count() <= 95)
        {
            window->setActive(true);
            window->draw(*c->paw_prints);
            window->setActive(false);
        }
        if (g->get_generation_count() >= 95 && g->get_generation_count() <= 100)
        {
            if (g->get_generation_count() == 95)
            {
                c->paw_prints->rotate(135);
            }
            window->setActive(true);
            window->draw(*c->paw_prints);
            window->setActive(false);
        }
        
    }
    else if (g->get_generation_count() >= 100 && g->get_generation_count() <= 110)
    {
        window->setActive(true);
        window->draw(*c->boom2);
        window->setActive(false);
    }
}

void draw_gol::call_big_boom(int pos_x, int pos_y) {
    g->big_boom(pos_x, pos_y);
}

void draw_gol::watch_gol()
{
    srand(time(nullptr));
    
    std::cout << "Generacija: " << g->get_generation_count() << endl;
    
    sf::RectangleShape cell_alive(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));
    cell_alive.setOutlineThickness(1);
    cell_alive.setOutlineColor(sf::Color::Yellow);

    int color_count = 64;
    if (g->get_generation_count() < 100)
    {
        sf::Color alive_color(gen_rnd(0, color_count), gen_rnd(0, color_count), gen_rnd(0, color_count));
        cell_alive.setFillColor(alive_color);
    }
    else if (g->get_generation_count() < 200)
    {
        sf::Color alive_color(gen_rnd(0, color_count * 2), gen_rnd(0, color_count * 2), gen_rnd(0, color_count * 2));
        cell_alive.setFillColor(alive_color);
    }
    else if (g->get_generation_count() < 400)
    {
        sf::Color alive_color(gen_rnd(0, color_count * 3), gen_rnd(0, color_count * 3), gen_rnd(0, color_count * 3));
        cell_alive.setFillColor(alive_color);
    }
    else
    {
        sf::Color alive_color(gen_rnd(0, color_count * 4 - 1), gen_rnd(0, color_count * 4 - 1), gen_rnd(0, color_count * 4 - 1));
        cell_alive.setFillColor(alive_color);
    }

    

    sf::RectangleShape cell_dead(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));
    sf::Color dead_color(10, 100, 100);
    cell_dead.setFillColor(dead_color);
    
    


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

void game_of_life::big_boom(int pos_x, int pos_y) {
    int row = pos_x / 10.0f;
    int col = pos_y / 10.0f;
    std::cout << "big_boom!" << endl;
    // kill the clicked cell and its 60 surrounding cells
    for (int i = row - 50; i <= row + 50; i++) {
        for (int j = col - 50; j <= col + 50; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < columns) {
                _next_gen[i][j] = false;

            }
        }
    }
    copy_next_to_curr();
}

void game_of_life::copy_next_to_curr() {
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
    copy_next_to_curr();
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
    copy_next_to_curr();
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
    copy_next_to_curr();
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