#include "Room.hpp"
#include <random>

Room::Room(int w, int h) : width(w), height(h), grid(h, std::vector<int>(w, WALL)) {}

void Room::setTile(int x, int y, TileType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) grid[y][x] = type;
}

TileType Room::getTile(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 && y < height) ? (TileType)grid[y][x] : WALL;
}

sf::IntRect Room::getBoundingBox() const {
    int minX = width, minY = height, maxX = 0, maxY = 0;
    bool found = false;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == FLOOR) {
                if (x < minX) minX = x;
                if (x > maxX) maxX = x;
                if (y < minY) minY = y;
                if (y > maxY) maxY = y;
                found = true;
            }
        }
    }

    if (!found) return sf::IntRect({0, 0}, {width, height});

    // SFML 3.0: Use the {position}, {size} constructor syntax
    return sf::IntRect({minX - 1, minY - 1}, {(maxX - minX) + 2, (maxY - minY) + 2});
}

void Room::clear(TileType type) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = type;
        }
    }
}

sf::Vector2i Room::getRandomTile(TileType type) const {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);

    while (true) {
        int x = xDist(gen);
        int y = yDist(gen);
        if (grid[y][x] == type) return {x, y};
    }
}