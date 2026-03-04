#include "roomGenerator.hpp"
#include <iostream>
#include <random>
#include <ctime>

RoomGenerator::RoomGenerator(int w, int h, int target) 
    : width(w), height(h), targetFloors(target) {
    grid.resize(height, std::vector<int>(width, WALL));
    // Note: std::srand is fine, but modern C++ often uses <random> 
    // We'll keep this for now to keep your logic simple.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void RoomGenerator::generate() {
    int x = width / 2;
    int y = height / 2;
    int floorsCreated = 0;

    // Safety check to ensure we don't start out of bounds
    if (grid[y][x] == WALL) {
        grid[y][x] = FLOOR;
        floorsCreated++;
    }

    while (floorsCreated < targetFloors) {
        int dir = std::rand() % 4;
        if (dir == 0 && y > 1) y--;
        else if (dir == 1 && y < height - 2) y++;
        else if (dir == 2 && x > 1) x--;
        else if (dir == 3 && x < width - 2) x++;

        if (grid[y][x] == WALL) {
            grid[y][x] = FLOOR;
            floorsCreated++;
        }
    }
}

void RoomGenerator::draw(sf::RenderWindow& window) {
    float tileSize = 10.0f;
    
    // SFML 3.0: sf::Vector2f now prefers {x, y} syntax
    sf::RectangleShape rect(sf::Vector2f{tileSize - 1.0f, tileSize - 1.0f});
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // SFML 3.0: setPosition takes a Vector2f {x, y}
            rect.setPosition({static_cast<float>(x) * tileSize, static_cast<float>(y) * tileSize});
            
            if (grid[y][x] == FLOOR) {
                rect.setFillColor(sf::Color(200, 200, 200)); // Light Gray
            } else {
                rect.setFillColor(sf::Color(30, 30, 30));    // Dark Gray
            }
            window.draw(rect);
        }
    }
}

void RoomGenerator::print() {
    for (const auto& row : grid) {
        for (int cell : row) std::cout << (cell == FLOOR ? "." : "#");
        std::cout << "\n";
    }
}