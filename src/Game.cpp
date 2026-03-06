#include "Game.hpp"

Game::Game() 
    : window(sf::VideoMode({800, 600}), "Dungeon Crawler"),
      room(70, 70),
      generator(1000),
      roomRenderer(24.0f) {
    
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
    // SFML 3.0: pollEvent() returns an std::optional<sf::Event>
    while (const std::optional event = window.pollEvent()) {
        
        // SFML 3.0: Use is<T> to check event types
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        // SFML 3.0: Use getIf<T> to access event data
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
    
    // SFML 3.0: Must use sf::Keyboard::Key::[Letter]
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

    // 1. Get the player's position using your existing getter
    sf::Vector2i pos = player->getGridPos();

    // 2. Convert to world pixels and snap to the nearest integer
    // This prevents sub-pixel shifting that causes grid line artifacts
    sf::Vector2f playerPos(
        std::round(static_cast<float>(pos.x) * tileSize), 
        std::round(static_cast<float>(pos.y) * tileSize)
    );

    // 3. Create the view using the SFML 3.0 vector-based constructor
    // The view center is the player, size is your window dimensions
    sf::View view(playerPos, {800.0f, 600.0f});
    
    window.setView(view);

    // 4. Draw elements
    roomRenderer.draw(window, room);
    playerRenderer.draw(window, *player, tileSize);
    
    window.display();
}