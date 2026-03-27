#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System.hpp>  // For sf::Vector2i and sf::Clock
#include "Room.hpp"         // For collision checking against the Room's grid

class Player {
public:
    Player(sf::Vector2i startPos);
    void move(sf::Vector2i direction, const Room& room);
    
    // Accessor for the move clock
    sf::Clock& getClock() { return moveClock; }

    sf::Vector2i getGridPos() const { return gridPos; }
    void setGridPos(sf::Vector2i pos) { gridPos = pos; }

private:
    sf::Vector2i gridPos;
    sf::Clock moveClock;
    const float movementDelay = 0.15f;
};

#endif