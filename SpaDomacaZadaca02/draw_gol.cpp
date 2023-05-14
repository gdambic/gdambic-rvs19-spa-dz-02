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
    c->rm_dance = new sf::RectangleShape(sf::Vector2f(450, 450));
    c->rm_danceTexture = new sf::Texture();
    c->rm_middle_finger = new sf::RectangleShape(sf::Vector2f(1200, 1200));
    c->rm_middle_fingerTexture = new sf::Texture();

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
    c->boom1->setPosition(950-200, 530-200);

    string boom2_texture_path = cwd + "/Pictures/boom2.png";
    if (!c->boom2Texture->loadFromFile(boom2_texture_path))
    {
        cout << "404 boom2" << endl;
    }

    c->boom2->setTexture(c->boom2Texture);
    c->boom2->setPosition(950-200, 530-200);

    string paw_prints_texture_path = cwd + "/Pictures/paw_prints.png";
    if (!c->paw_printsTexture->loadFromFile(paw_prints_texture_path))
    {
        cout << "404 paw_prints" << endl;
    }

    c->paw_prints->setTexture(c->paw_printsTexture);
    c->paw_prints->setPosition(950, 530);


    string rm_dance_texture_path = cwd + "/Pictures/rm_dance.png";
    if (!c->rm_danceTexture->loadFromFile(rm_dance_texture_path))
    {
        cout << "404 rm_dance" << endl;
    }

    c->rm_dance->setTexture(c->rm_danceTexture);
    c->rm_dance->setPosition(950, 530);

    string rm_middle_finger_texture_path = cwd + "/Pictures/rm_middle_finger.png";
    if (!c->rm_middle_fingerTexture->loadFromFile(rm_middle_finger_texture_path))
    {
        cout << "404 rm_middle_finger" << endl;
    }

    c->rm_middle_finger->setTexture(c->rm_middle_fingerTexture);
    c->rm_middle_finger->setPosition(950, 530);



    //Loading the font
    if (!font.loadFromFile("LibreBaskerville-Regular.ttf"))
    {
        cout << "font 404" << endl;
    }

}

void draw_gol::cat_falling(int start, int finish) {

    if (g->get_generation_count() >= start && g->get_generation_count() <= finish-1)
    {
        write_text_to_screen("> Lucifer no! Bad cat!", 200, 100);
        int newPosX = -120;
        int newPosY = -150 + g->get_generation_count() * 5;
        c->catFalling->setPosition(newPosX, newPosY);
        window->setActive(true);
        window->draw(*c->catFalling);
        window->setActive(false);
    }
    if (g->get_generation_count() == finish-1)
    {
        g->kill_cells(200, 100, 30);
    }
    
}

void draw_gol::scratching(int start, int finish) {

    srand(time(nullptr));
    
    if (g->get_generation_count() >= start && g->get_generation_count() <= finish)
    {
        for (size_t i = g->get_generation_count() - start; i < finish; i++)
        {
            int x = gen_rnd(0, 1900);
            int y = gen_rnd(0, 1900);
            c->scratches->setPosition(x, y);
            window->setActive(true);
            window->draw(*c->scratches);
            window->setActive(false);
        }
        
    }
    
}

void draw_gol::curious_streach(int start, int finish) {

    if (g->get_generation_count() >= start && g->get_generation_count() <= start+15)
    {
        window->setActive(true);
        window->draw(*c->curious_1);
        window->setActive(false);
    }
    else if (g->get_generation_count() >= start+15 && g->get_generation_count() <= finish)
    {
        window->setActive(true);
        window->draw(*c->streach_2);
        window->setActive(false);
    }

}

void draw_gol::boom(int start, int finish) { // 220 260

    if (g->get_generation_count() >= start && g->get_generation_count() <= start+20)
    {
        if (g->get_generation_count() >= start && g->get_generation_count() <= start+10)
        {
            window->setActive(true);
            window->draw(*c->paw_prints);
            window->setActive(false);
        }
        if (g->get_generation_count() >= start+10 && g->get_generation_count() <= finish-20)
        {   
            window->setActive(true);
            window->draw(*c->boom1);
            window->setActive(false);
        }
        
    }
    else if (g->get_generation_count() >= finish-20 && g->get_generation_count() < finish)
    {
        write_text_to_screen("> Lucifer no! Where did you find that??", 950 - 300, 530 - 300);
        window->setActive(true);
        window->draw(*c->boom2);
        window->setActive(false);
    }
    else if (g->get_generation_count() == finish)
    {
        sf::Vector2u windowSize = window->getSize();

        // Calculate the center coordinates
        float centerX = windowSize.x / 2.0f;
        float centerY = windowSize.y / 2.0f;
        std::cout << "Center X: " << centerX << std::endl;
        std::cout << "Center Y: " << centerY << std::endl;
        g->big_boom(centerX, centerY);
    }
}

void draw_gol::write_text_to_screen(string text, int posX, int posY) {

    sf::Text textBox;
    textBox.setCharacterSize(50);
    textBox.setFont(font);
    textBox.setFillColor(sf::Color::Red);
    textBox.setOutlineColor(sf::Color::Black);
    textBox.setOutlineThickness(50);
    textBox.setString(text);
    textBox.setPosition(posX, posY);

    window->setActive(true);
    window->draw(textBox);
    window->setActive(false);
}

void draw_gol::write_text_to_screen(string text, int posX, int posY, int start, int finish) {
   
    if (g->get_generation_count() >= start && g->get_generation_count() <= finish)
    {
        sf::Text textBox;
        textBox.setCharacterSize(50);
        textBox.setFont(font);
        textBox.setFillColor(sf::Color::Red);
        textBox.setOutlineColor(sf::Color::Black);
        textBox.setOutlineThickness(50);
        textBox.setString(text);
        textBox.setPosition(posX, posY);

        window->setActive(true);
        window->draw(textBox);
        window->setActive(false);
    }
    
}

void draw_gol::rm_dance(int start, int finish) {
    if (g->get_generation_count() >= start && g->get_generation_count() <= finish)
    {
        int newPosX = window->getSize().x - c->rm_dance->getSize().x / finish - g->get_generation_count() - 400;
        int newPosY = window->getSize().y - c->rm_dance->getSize().y;
        c->rm_dance->setPosition(newPosX, newPosY);
        
        window->setActive(true);
        window->draw(*c->rm_dance);
        window->setActive(false);
    }
    if (g->get_generation_count() >= finish - 30 && g->get_generation_count() <= finish)
    {
        write_text_to_screen("Wait *burp* Morty, that's the cat!\n Get the cat!!", 650, 270);
    }
}

void draw_gol::rm_middle_finger(int start, int finish) {

    if (g->get_generation_count() >= start && g->get_generation_count() <= finish)
    {
        int newPosX = (window->getSize().x - c->rm_middle_finger->getSize().x) / 2;
        int newPosY = (window->getSize().y - c->rm_middle_finger->getSize().y) / 2;
        c->rm_middle_finger->setPosition(newPosX, newPosY);

        window->setActive(true);
        window->draw(*c->rm_middle_finger);
        window->setActive(false);
    }
}

void draw_gol::call_big_boom(int pos_x, int pos_y, int when) {
    if (g->get_generation_count() == when)
    {
        g->big_boom(pos_x, pos_y);
    }
    
}

void draw_gol::call_kill_all(int when) {
    if (g->get_generation_count() == when)
    {
        g->kill_all();
    }
}

void draw_gol::watch_gol()
{
    srand(time(nullptr));
    
    std::cout << "Generacija: " << g->get_generation_count() << endl;
    
    sf::RectangleShape cell_alive(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));
    cell_alive.setOutlineThickness(1);
    cell_alive.setOutlineColor(sf::Color::Yellow);

    sf::RectangleShape cell_dead(sf::Vector2f(g->get_cell_size(), g->get_cell_size()));

    int color_count = 64;
    if (g->get_generation_count() < 100)
    {
        sf::Color alive_color(gen_rnd(0, color_count), gen_rnd(0, color_count), gen_rnd(0, color_count));
        cell_alive.setFillColor(alive_color);
        sf::Color dead_color(10, 100, 100);
        cell_dead.setFillColor(dead_color);
    }
    else if (g->get_generation_count() < 200)
    {
        sf::Color alive_color(gen_rnd(0, color_count * 2), gen_rnd(0, color_count * 2), gen_rnd(0, color_count * 2));
        cell_alive.setFillColor(alive_color);
        sf::Color dead_color(10, 100, 100);
        cell_dead.setFillColor(dead_color);
    }
    else if (g->get_generation_count() < 400)
    {
        sf::Color alive_color(gen_rnd(0, color_count * 3), gen_rnd(0, color_count * 3), gen_rnd(0, color_count * 3));
        cell_alive.setFillColor(alive_color);
        sf::Color dead_color(10, 100, 100);
        cell_dead.setFillColor(dead_color);
    }
    else if (g->get_generation_count() >= 400 && g->get_generation_count() <= 620)
    {
        sf::Color alive_color(gen_rnd(0, color_count * 4 - 1), gen_rnd(0, color_count * 4 - 1), gen_rnd(0, color_count * 4 - 1));
        cell_alive.setFillColor(alive_color);
        sf::Color dead_color(10, 100, 100);
        cell_dead.setFillColor(dead_color);
    }
    else
    {
        sf::Color alive_color(gen_rnd(0, 255), gen_rnd(0, 255), gen_rnd(0, 255));
        cell_alive.setFillColor(alive_color);
        sf::Color dead_color(gen_rnd(0, 255), gen_rnd(0, 255), gen_rnd(0, 255));
        cell_dead.setFillColor(dead_color);
    }

    window->setActive(true);
    
    window->clear();
    
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

void game_of_life::kill_all() {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            _next_gen[i][j] = false;
        }
    }
    copy_next_to_curr();
}

void game_of_life::kill_cells(int x, int y, int no_of_cells_to_kill) {
    int row = x / 10.0f;
    int col = y / 10.0f;

    // kill the clicked cell and the specified number of surrounding cells
    int startRow = std::max(0, row - no_of_cells_to_kill);
    int endRow = std::min((unsigned int)rows - 1, (unsigned int)row + no_of_cells_to_kill);
    int startCol = std::max(0, col - no_of_cells_to_kill);
    int endCol = std::min((unsigned int)columns - 1, (unsigned int)col + no_of_cells_to_kill);

    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            _next_gen[i][j] = false;
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