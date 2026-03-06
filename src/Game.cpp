#include "Game.hpp"
#include <cmath> 

Game::Game() 
    // 1. Get the desktop resolution directly
    : window(sf::VideoMode(sf::VideoMode::getDesktopMode().size), 
             "Dungeon Crawler", 
             sf::Style::Default),
      room(70, 70),
      generator(1000),
      roomRenderer(24.0f) {
    
    // 2. Enable VSync to stop the flickering
    window.setVerticalSyncEnabled(true);
    
    generator.generate(room);
    player = std::make_unique<Player>(room.getRandomTile(FLOOR));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::R) {
                generator.generate(room);
                player->setGridPos(room.getRandomTile(FLOOR));
            }
        }
    }
}

void Game::update() {
    sf::Vector2i dir(0, 0);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dir.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dir.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dir.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dir.x += 1;

    if (dir.x != 0 || dir.y != 0) {
        player->move(dir, room);
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    float tileSize = 24.0f;
    sf::Vector2i pos = player->getGridPos();

    // 3. Center the camera on the player (snapped to whole pixels)
    sf::Vector2f playerPos(
        std::round(static_cast<float>(pos.x) * tileSize), 
        std::round(static_cast<float>(pos.y) * tileSize)
    );

    // 4. Set the view size to match the window's actual interior size
    // This allows you to resize the window and see more/less of the world
    sf::Vector2f viewSize(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)
    );

    sf::View view(playerPos, viewSize);
    window.setView(view);

    roomRenderer.draw(window, room);
    playerRenderer.draw(window, *player, tileSize);
    
    window.display();
}