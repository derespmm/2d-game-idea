#include "roomGenerator.hpp"
#include "Player.hpp"

int main() {
    // 1. Get the laptop dimensions once
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenW = desktop.size.x;
    unsigned int screenH = desktop.size.y;

    // 2. Create the Window (using sf::State for SFML 3.0)
    sf::RenderWindow window(sf::VideoMode({screenW, screenH}), "Stealth Game", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    // 3. Define the "Camera" (View)
    // Map is 70x70 tiles * 10px per tile = 700x700 area
    sf::View gameView(sf::FloatRect({0.f, 0.f}, {700.f, 700.f}));
    gameView.setViewport(sf::FloatRect({(1.f - (float)screenH/screenW)/2.f, 0.f}, {(float)screenH/screenW, 1.f}));
    window.setView(gameView);

    // 4. Initialize the Room
    RoomGenerator room(70, 70, 1500);
    room.generate();

    // Initial Spawns
    auto spawns = room.getRandomSpawns();
    Player player(spawns.playerStart.x, spawns.playerStart.y);
    sf::Vector2i doorPos = spawns.doorLocation;

    // Door Visuals
    sf::RectangleShape doorShape({10.f, 10.f});
    doorShape.setFillColor(sf::Color::Yellow); // Gold/Yellow for the door

    while (window.isOpen()) {
        // --- EVENT POLLING ---
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) window.close();
                
                // Manual Reset with 'R'
                if (keyPressed->code == sf::Keyboard::Key::R) {
                    room.generate();
                    auto s = room.getRandomSpawns();
                    player.setPosition(s.playerStart);
                    doorPos = s.doorLocation;
                }
            }
        }

        // --- GAME LOGIC ---
        player.update(room.getGrid());

        // Check if Player reached the Door
        if (player.getGridPos() == doorPos) {
            room.generate(); // Create new layout
            auto nextSpawns = room.getRandomSpawns();
            player.setPosition(nextSpawns.playerStart);
            doorPos = nextSpawns.doorLocation;
        }

        // --- RENDERING ---
        window.clear(sf::Color(10, 10, 10));
        
        room.draw(window);
        
        // Draw Door
        doorShape.setPosition({static_cast<float>(doorPos.x * 10), static_cast<float>(doorPos.y * 10)});
        window.draw(doorShape);

        player.draw(window);
        
        window.display();
    }

    return 0;
}