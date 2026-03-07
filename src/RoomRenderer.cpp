#include "RoomRenderer.hpp"

RoomRenderer::RoomRenderer(float t) : tileSize(t), floorRect({t - 1, t - 1}), wallRect({t - 1, t - 1}) {
    floorRect.setFillColor(sf::Color(200, 200, 200));
    wallRect.setFillColor(sf::Color(30, 30, 30));
}

void RoomRenderer::draw(sf::RenderWindow& window, const Room& room) {
    for (int x = 0; x < room.getWidth(); ++x) {
        for (int y = 0; y < room.getHeight(); ++y) {
            
            TileType type = room.getTile(x, y);

            // ONLY draw if the tile is a WALL or a FLOOR
            if (type == WALL || type == FLOOR) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition({static_cast<float>(x * tileSize), 
                                  static_cast<float>(y * tileSize)});
                
                // Color the tiles (Change these to your preferred colors)
                if (type == WALL) {
                    tile.setFillColor(sf::Color(0, 0, 0)); // Dark grey walls
                } else {
                    tile.setFillColor(sf::Color(150, 150, 150)); // Darker grey floors
                }
                
                window.draw(tile);
            }
            // By NOT drawing anything here, the background (which is black) 
            // will show through the empty cells!
        }
    }
}