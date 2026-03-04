#ifndef ROOM_GENERATOR_HPP
#define ROOM_GENERATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>

enum Tile { WALL = 0, FLOOR = 1 };

class RoomGenerator {
public:
    RoomGenerator(int w, int h, int target);
    void generate();
    void draw(sf::RenderWindow& window);
    void print(); 
    void clearRoom();
    const std::vector<std::vector<int>>& getGrid() const { return grid; }
    struct SpawnPoints {
        sf::Vector2i playerStart;
        sf::Vector2i doorLocation;
    };

    SpawnPoints getRandomSpawns() const;

private:
    int width, height, targetFloors;
    std::vector<std::vector<int>> grid;
};

#endif