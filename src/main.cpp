#include "roomGenerator.hpp"

int main() {
    // SFML 3.0 uses sf::Vector2u inside VideoMode
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Stealth Game - Room Gen");

    RoomGenerator room(70, 70, 1500);
    room.generate();

    // SFML 3.0 event loop returns std::optional
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            
            // Check for Window Closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Check for Key Presses
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::R) {
                    room = RoomGenerator(70, 70, 1500);
                    room.generate();
                }
            }
        }

        window.clear(sf::Color(10, 10, 10)); // Darker background
        room.draw(window);
        window.display();
    }

    return 0;
}