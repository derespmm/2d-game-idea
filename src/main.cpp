#include "roomGenerator.hpp"

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

    while (window.isOpen()) {
        // SFML 3.0 event loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Exit game with Escape key (useful for Fullscreen!)
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                // Regenerate Room with 'R'
                if (keyPressed->code == sf::Keyboard::Key::R) {
                    room = RoomGenerator(70, 70, 1500);
                    room.generate();
                }
            }
        }

        window.clear(sf::Color(10, 10, 10));
        
        // Everything drawn here is automatically zoomed by gameView
        room.draw(window); 
        
        window.display();
    }

    return 0;
}