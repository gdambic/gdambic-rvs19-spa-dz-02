#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

const int N = 30; // kolicina tocaka
const int STEPS = 100;
const int DELAY = 2000;
const int DOT_SIZE = 10;

int main() {
    sf::RenderWindow window(sf::VideoMode(N * DOT_SIZE, N * DOT_SIZE), "Igra života");

    std::vector<std::vector<int>> grid(N, std::vector<int>(N));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dis(gen) < 25) {
                grid[i][j] = 1;
            }
            else {
                grid[i][j] = 0;
            }
        }
    }

    for (int step = 0; step < STEPS; step++) {
        std::cout << "Korak " << step << ":\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << "\n";
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        std::vector<std::vector<int>> new_grid(N, std::vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // broj živih 
                int count = 0;
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x == 0 && y == 0) continue;
                        int i2 = (i + x + N) % N;
                        int j2 = (j + y + N) % N;
                        if (grid[i2][j2] == 1) count++;
                    }
                }

                // pravila 
                if (grid[i][j] == 1) {
                    if (count < 2 || count > 3) {
                        new_grid[i][j] = 0;
                    }
                    else {
                        new_grid[i][j] = 1;
                    }
                }
                else {
                    if (count == 3) {
                        new_grid[i][j] = 1;
                    }
                    else {
                        new_grid[i][j] = 0;
                    }
                }
            }
        }
        window.clear();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 1) {
                    sf::CircleShape dot(DOT_SIZE / 2.0);
                    dot.setPosition(i * DOT_SIZE, j * DOT_SIZE);
                    dot.setFillColor(sf::Color::White);
                    window.draw(dot);
                }
            }
        }
        window.display();
        grid = new_grid;
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

    }

    return 0;
}
