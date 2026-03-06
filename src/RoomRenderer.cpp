#include "RoomRenderer.hpp"

RoomRenderer::RoomRenderer(float t) : tileSize(t), floorRect({t - 1, t - 1}), wallRect({t - 1, t - 1}) {
    floorRect.setFillColor(sf::Color(200, 200, 200));
    wallRect.setFillColor(sf::Color(30, 30, 30));
}

void RoomRenderer::draw(sf::RenderWindow& window, const Room& room) {
    for (int y = 0; y < room.getHeight(); ++y) {
        for (int x = 0; x < room.getWidth(); ++x) {
            sf::RectangleShape& rect = (room.getTile(x, y) == FLOOR) ? floorRect : wallRect;
            rect.setPosition({x * tileSize, y * tileSize});
            window.draw(rect);
        }
    }
}