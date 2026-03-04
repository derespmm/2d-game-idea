#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "roomGenerator.hpp"

class Player {
public:
    Player(int startX, int startY);
    void handleInput();
    void update(const std::vector<std::vector<int>>& grid);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2i newPos);
    sf::Vector2i getGridPos() const { return gridPos; }

private:
    sf::RectangleShape shape;
    sf::Vector2i gridPos; // Tracking position in grid coordinates (0, 1, 2...)
    float movementDelay = 0.15f; // Prevents flying across the screen too fast
    sf::Clock moveClock;
};

#endif