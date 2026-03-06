#include "RoomGenerator.hpp"

RoomGenerator::RoomGenerator(int target) : targetFloors(target), rng(std::random_device{}()) {}

void RoomGenerator::generate(Room& room) {
    room.clear(WALL);
    
    int x = room.getWidth() / 2;
    int y = room.getHeight() / 2;
    int floors = 0;
    
    // Safety: don't loop forever if the map gets crowded
    int maxAttempts = (room.getWidth() * room.getHeight()) * 2; 
    int attempts = 0;

    std::uniform_int_distribution<int> dist(0, 3);

    while (floors < targetFloors && attempts < maxAttempts) {
        attempts++;
        
        if (room.getTile(x, y) == WALL) {
            room.setTile(x, y, FLOOR);
            floors++;
        }
        
        int dir = dist(rng);
        if (dir == 0 && y > 1) y--;
        else if (dir == 1 && y < room.getHeight() - 2) y++;
        else if (dir == 2 && x > 1) x--;
        else if (dir == 3 && x < room.getWidth() - 2) x++;
    }
}