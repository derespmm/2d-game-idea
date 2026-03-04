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
    void print(); // Added this back for your console testing

private:
    int width, height, targetFloors;
    std::vector<std::vector<int>> grid;
};

#endif