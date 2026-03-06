#include "Player.hpp"

Player::Player(sf::Vector2i startPos) : gridPos(startPos) {}

void Player::move(sf::Vector2i dir, const Room& room) {
    if (moveClock.getElapsedTime().asSeconds() < movementDelay) return;
    
    sf::Vector2i next = gridPos + dir;
    if (room.getTile(next.x, next.y) == FLOOR) {
        gridPos = next;
        moveClock.restart();
    }
}