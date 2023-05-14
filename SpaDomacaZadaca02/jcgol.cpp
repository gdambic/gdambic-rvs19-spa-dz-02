#include "jcgol.h"
#include <random>
#include <iostream>
#include <SFML/Audio.hpp>
//this part is changeable, just keep the ratio 16:9 and ideally 1920x1080 / CELL_SIZE
const int CELL_SIZE = 30;
const int NUM_X_CELLS = 64;
const int NUM_Y_CELLS = 36;

std::vector<std::vector<bool>> cells(NUM_Y_CELLS, std::vector<bool>(NUM_X_CELLS, 0));
int speed = 10;

//count all the neighbouring cells
int count_neighbours(int x, int y){
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            int nx = x + j;
            int ny = y + i;

            if (nx >= 0 && nx < NUM_X_CELLS && ny >= 0 && ny < NUM_Y_CELLS)
            {
                if (cells[ny][nx] == 1)
                    count++;
            }
        }
    }

    return count;
}

//update cell field
void update_cell_field(){
    std::vector<std::vector<bool>> new_cells(NUM_Y_CELLS, std::vector<bool>(NUM_X_CELLS, 0));

    for (int y = 0; y < NUM_Y_CELLS; y++)
    {
        for (int x = 0; x < NUM_X_CELLS; x++)
        {
            int neighbours = count_neighbours(x, y);

            if (cells[y][x] == 1 && (neighbours == 2 || neighbours == 3))
                new_cells[y][x] = 1;
            else if (cells[y][x] == 0 && neighbours == 3)
                new_cells[y][x] = 1;
            else
                new_cells[y][x] = 0;
        }
    }

    cells = new_cells;
}

//main function, with manually assigned cells
void jcgol::display(sf::RenderWindow& window){
    sf::SoundBuffer buffer;
    sf::Sound click;
    try {
        if (!buffer.loadFromFile("Resources\\click.ogg")) {
            throw std::runtime_error("Error loading click sound! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what(); }
    click.setBuffer(buffer);
    click.play();

    bool paused = true;

    sf::Clock clock;

    sf::Texture alive_texture;
    try {
        if (!alive_texture.loadFromFile("Resources\\alive.jpg")) {
            throw std::runtime_error("Error loading live cell texture! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what() << std::endl; }

    sf::Texture dead_texture;
    try {
        if (!dead_texture.loadFromFile("Resources\\dead.png")) {
            throw std::runtime_error("Error loading dead cell texture! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what() << std::endl; }

    dead_texture.setRepeated(true);
    sf::Sprite dead(dead_texture);




    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    paused = !paused;
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x / CELL_SIZE;
                    int y = event.mouseButton.y / CELL_SIZE;
                    cells[y][x] = !cells[y][x];
                }
                break;

            case sf::Event::MouseWheelMoved:
                speed += event.mouseWheel.delta;
                if (speed < 1)
                    speed = 1;
                std::cout <<"Speed: " <<speed << std::endl;
                break;
            }
        }

        if (!paused)
        {
            float elapsed_time = clock.getElapsedTime().asSeconds();

            if (elapsed_time >= 1.0f / speed)
            {
                update_cell_field();
                clock.restart();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(dead);

        for (int y = 0; y < NUM_Y_CELLS; y++)
        {
            for (int x = 0; x < NUM_X_CELLS; x++)
            {
                if (cells[y][x] == 1)
                {
                    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    rect.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    rect.setTexture(&alive_texture);
                    window.draw(rect);
                }
            }
        }

        window.display();
    }
}

void jcgol::display_random(sf::RenderWindow& window)
{
    sf::SoundBuffer buffer;
    sf::Sound click;
    try {
        if (!buffer.loadFromFile("Resources\\click.ogg")) {
            throw std::runtime_error("Error loading click sound! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what(); }
    click.setBuffer(buffer);
    click.play();

    bool paused = true;

    sf::Clock clock;

    sf::Texture alive_texture;
    try {
        if (!alive_texture.loadFromFile("Resources\\alive.jpg")) {
            throw std::runtime_error("Error loading live cell texture! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what() << std::endl; }

    sf::Texture dead_texture;
    try {
        if (!dead_texture.loadFromFile("Resources\\dead.png")) {
            throw std::runtime_error("Error loading dead cell texture! 404, not found!");
        }
    }
    catch (std::runtime_error err) { std::cout << err.what() << std::endl; }

    dead_texture.setRepeated(true);
    sf::Sprite dead(dead_texture);


    bool n[4] = {0,0,0,1};
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[0].size(); j++) {
            std::shuffle(&n[0], &n[4], std::mt19937(std::random_device()()));
            if(n[0])
            cells[i][j] = 1;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    paused = !paused;
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x / CELL_SIZE;
                    int y = event.mouseButton.y / CELL_SIZE;
                    cells[y][x] = !cells[y][x];

                }
                break;

            case sf::Event::MouseWheelMoved:
                speed += event.mouseWheel.delta;
                if (speed < 1)
                    speed = 1;
                std::cout << "Speed: " <<speed<< std::endl;
                break;
            }
        }

        if (!paused)
        {
            float elapsed_time = clock.getElapsedTime().asSeconds();

            if (elapsed_time >= 1.0f / speed)
            {
                update_cell_field();
                clock.restart();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(dead);

        for (int y = 0; y < NUM_Y_CELLS; y++)
        {
            for (int x = 0; x < NUM_X_CELLS; x++)
            {
                if (cells[y][x] == 1)
                {
                    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    rect.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    rect.setTexture(&alive_texture);
                    window.draw(rect);
                }
            }
        }

        window.display();
    }
}