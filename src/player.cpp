#include "Player.hpp"

Player::Player(int startX, int startY) : gridPos(startX, startY) {
    shape.setSize({10.0f, 10.0f}); // Match tile size
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({static_cast<float>(gridPos.x * 10), static_cast<float>(gridPos.y * 10)});
}

void Player::update(const std::vector<std::vector<int>>& grid) {
    // Only move every 0.15 seconds so it's controllable
    if (moveClock.getElapsedTime().asSeconds() < movementDelay) return;

    sf::Vector2i dir(0, 0);

    // WASD or Arrow Keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    dir.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  dir.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  dir.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dir.x = 1;

    if (dir.x != 0 || dir.y != 0) {
        int nextX = gridPos.x + dir.x;
        int nextY = gridPos.y + dir.y;

        // Collision Check: Stay within bounds and only walk on FLOOR
        if (nextY >= 0 && nextY < (int)grid.size() && nextX >= 0 && nextX < (int)grid[0].size()) {
            if (grid[nextY][nextX] == FLOOR) {
                gridPos = {nextX, nextY};
                shape.setPosition({static_cast<float>(gridPos.x * 10), static_cast<float>(gridPos.y * 10)});
                moveClock.restart();
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Player::setPosition(sf::Vector2i newPos) {
    gridPos = newPos;
    // Update the visual box to match the new grid math
    shape.setPosition({static_cast<float>(gridPos.x * 10), static_cast<float>(gridPos.y * 10)});
}