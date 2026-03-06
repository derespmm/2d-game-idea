#include "Game.hpp"

int main() {
    // Everything is encapsulated in the Game class
    Game game;
    
    // The Game class handles the loop, window, and rendering
    game.run();
    
    return 0;
}