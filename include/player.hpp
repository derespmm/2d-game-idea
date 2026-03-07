#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System.hpp>  // For sf::Vector2i and sf::Clock
#include "Room.hpp"         // For collision checking against the Room's grid

class Player {
public:
    Player(sf::Vector2i startPos);
    void move(sf::Vector2i direction, const Room& room);

    // Getters/Setters for the movement logic
    sf::Vector2i getLastDir() const { return lastDir; }
    void setLastDir(sf::Vector2i dir) { lastDir = dir; }
    
    // Accessor for the move clock
    sf::Clock& getClock() { return moveClock; }

    sf::Vector2i getGridPos() const { return gridPos; }
    void setGridPos(sf::Vector2i pos) { gridPos = pos; }

private:
    sf::Vector2i gridPos;
    sf::Vector2i lastDir = {0, 0}; // Tracks the direction of the previous movement
    sf::Clock moveClock;
    const float movementDelay = 0.15f;
};

#endif