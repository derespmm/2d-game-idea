#include "RoomGenerator.hpp"

RoomGenerator::RoomGenerator(int target) : targetFloors(target), rng(std::random_device{}()) {}

void RoomGenerator::generate(Room& room) {
    room.clear(WALL);
    
    // Start exactly in the center
    int x = room.getWidth() / 2;
    int y = room.getHeight() / 2;
    int floors = 0;
    
    int maxAttempts = (room.getWidth() * room.getHeight()) * 2; 
    int attempts = 0;

    std::uniform_int_distribution<int> dist(0, 3);

    while (floors < targetFloors && attempts < maxAttempts) {
        attempts++;
        
        // 1. Only place the floor if we are within the actual grid
        if (x >= 0 && x < room.getWidth() && y >= 0 && y < room.getHeight()) {
            if (room.getTile(x, y) == WALL) {
                room.setTile(x, y, FLOOR);
                floors++;
            }
        }
        
        // 2. Original movement: No clamping, no gravity, just pure random walk
        int dir = dist(rng);
        if (dir == 0) y--;
        else if (dir == 1) y++;
        else if (dir == 2) x--;
        else if (dir == 3) x++;
    }
}