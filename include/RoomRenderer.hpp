#ifndef ROOM_RENDERER_HPP
#define ROOM_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Room.hpp"

class RoomRenderer {
public:
    RoomRenderer(float tileSize = 10.0f);
    void draw(sf::RenderWindow& window, const Room& room);

private:
    float tileSize;
    sf::RectangleShape floorRect;
    sf::RectangleShape wallRect;
};

#endif