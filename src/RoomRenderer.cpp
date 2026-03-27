#include "RoomRenderer.hpp"

RoomRenderer::RoomRenderer(float t) : tileSize(t), floorRect({t - 1, t - 1}), wallRect({t - 1, t - 1}) {
    floorRect.setFillColor(sf::Color(150, 150, 150)); // Floor color
    wallRect.setFillColor(sf::Color(0, 0, 0));         // Wall color
}

void RoomRenderer::draw(sf::RenderWindow& window, const Room& room) {
    sf::Vector2i doorPos = room.getDoorPos(); // Fetch the door position

    for (int x = 0; x < room.getWidth(); ++x) {
        for (int y = 0; y < room.getHeight(); ++y) {
            
            TileType type = room.getTile(x, y);

            // 1. Determine which base tile to draw
            if (type == WALL || type == FLOOR) {
                sf::RectangleShape* currentTile = (type == WALL) ? &wallRect : &floorRect;
                currentTile->setPosition({static_cast<float>(x * tileSize), 
                                          static_cast<float>(y * tileSize)});
                window.draw(*currentTile);
            }

            // 2. Override with the Door if it matches our coordinates
            if (x == doorPos.x && y == doorPos.y) {
                sf::RectangleShape doorTile({tileSize - 1, tileSize - 1});
                doorTile.setPosition({static_cast<float>(x * tileSize), 
                                      static_cast<float>(y * tileSize)});
                doorTile.setFillColor(sf::Color::Yellow);
                window.draw(doorTile);
            }
        }
    }
}