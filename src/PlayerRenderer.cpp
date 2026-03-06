#include "PlayerRenderer.hpp"
#include "Player.hpp"

void PlayerRenderer::draw(sf::RenderWindow& window, const Player& player, float tileSize) {
    sf::RectangleShape shape({tileSize - 1, tileSize - 1});
    shape.setFillColor(sf::Color::Green);
    sf::Vector2i pos = player.getGridPos();
    shape.setPosition({pos.x * tileSize, pos.y * tileSize});
    window.draw(shape);
}