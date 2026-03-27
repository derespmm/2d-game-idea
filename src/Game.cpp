#include "Game.hpp"
#include <cmath> 

Game::Game() 
    // 1. Get the desktop resolution directly
    : window(sf::VideoMode(sf::VideoMode::getDesktopMode().size), 
             "Dungeon Crawler", 
             sf::Style::Default),
      room(120, 120),
      generator(7000),
      roomRenderer(24.0f) {
    
    // 2. Enable VSync to stop the flickering
    window.setVerticalSyncEnabled(true);
    
    generator.generate(room);

    sf::Vector2i startPos = room.getRandomTile(FLOOR);
    player = std::make_unique<Player>(startPos);
    
    // Initialize camera exactly on the player to start
    cameraPos = { static_cast<float>(startPos.x * 24.0f), 
                  static_cast<float>(startPos.y * 24.0f) };
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

    // New Level Check
    if (player->getGridPos() == room.getDoorPos()) {
        generator.generate(room);
        player->setGridPos(room.getRandomTile(FLOOR));
        // Optional: Ensure the door isn't immediately under the player
        // by picking a new door position here if needed
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    float tileSize = 24.0f;
    sf::Vector2i pos = player->getGridPos();

    // 1. Where we WANT the camera to be
    sf::Vector2f targetPos(
        static_cast<float>(pos.x) * tileSize, 
        static_cast<float>(pos.y) * tileSize
    );

    // 2. Smoothly move cameraPos toward targetPos
    // The 0.1f value controls the "snappiness". 
    // Higher (e.g., 0.2f) = faster, Lower (e.g., 0.05f) = slower/lazier.
    float smoothing = 0.1f; 
    cameraPos.x += (targetPos.x - cameraPos.x) * smoothing;
    cameraPos.y += (targetPos.y - cameraPos.y) * smoothing;

    // 3. Create view using our smoothed cameraPos
    sf::View view(cameraPos, {static_cast<float>(window.getSize().x), 
                              static_cast<float>(window.getSize().y)});
    
    window.setView(view);

    roomRenderer.draw(window, room);
    playerRenderer.draw(window, *player, tileSize);
    
    window.display();
}