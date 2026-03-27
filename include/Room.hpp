#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <SFML/Graphics.hpp>

enum TileType { WALL, FLOOR };

class Room {
public:
    Room(int w, int h);
    
    void setTile(int x, int y, TileType type);
    TileType getTile(int x, int y) const;
    void clear(TileType type = WALL);

    sf::IntRect getBoundingBox() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    // Logic for finding points of interest
    sf::Vector2i getRandomTile(TileType type) const;

    sf::Vector2i getDoorPos() const { return doorPos; }
    void setDoorPos(sf::Vector2i pos) { doorPos = pos; }

private:
    int width, height;
    std::vector<std::vector<int>> grid;
    sf::Vector2i doorPos;
};

#endif