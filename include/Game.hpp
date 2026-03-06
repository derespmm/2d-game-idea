#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Room.hpp"
#include "RoomGenerator.hpp"
#include "RoomRenderer.hpp"
#include "Player.hpp"
#include "PlayerRenderer.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Room room;
    RoomGenerator generator;
    RoomRenderer roomRenderer; // THIS MUST MATCH GAME.CPP
    std::unique_ptr<Player> player; // THIS MUST MATCH GAME.CPP
    PlayerRenderer playerRenderer;   // THIS MUST MATCH GAME.CPP
    float tileSize = 12.0f;
};

#endif