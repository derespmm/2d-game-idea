#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System.hpp>  // For sf::Vector2i and sf::Clock
#include "Room.hpp"         // For collision checking against the Room's grid

class Player {
public:
    Player(sf::Vector2i startPos);

    /**
     * @brief Attempts to move the player in a given direction.
     * @param direction The movement vector (e.g., {0, -1} for up).
     * @param room Reference to the current map for collision detection.
     */
    void move(sf::Vector2i direction, const Room& room);

    sf::Vector2i getGridPos() const { return gridPos; }
    void setGridPos(sf::Vector2i pos) { gridPos = pos; }

private:
    sf::Vector2i gridPos;
    sf::Clock moveClock;
    const float movementDelay = 0.15f;
};

#endif