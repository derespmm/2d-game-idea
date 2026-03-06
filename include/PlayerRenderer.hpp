#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Forward declaration: We tell the compiler "A Player class exists" 
// without needing to include the heavy Player.hpp file.
class Player;

class PlayerRenderer {
public:
    // Pass the player by const reference to ensure we don't modify it
    void draw(sf::RenderWindow& window, const Player& player, float tileSize);
};

#endif