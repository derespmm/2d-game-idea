#include "RoomGenerator.hpp"
#include <queue>

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

    removeDisconnectedTiles(room);

    sf::Vector2i doorPos = room.getRandomTile(FLOOR);
    room.setDoorPos(doorPos); // Pass the door location to the Room object
}

void RoomGenerator::removeDisconnectedTiles(Room& room) {
    // Find any floor tile to start the fill from
    sf::Vector2i start = room.getRandomTile(FLOOR);
    
    int width = room.getWidth();
    int height = room.getHeight();
    
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::queue<sf::Vector2i> toVisit;
    
    toVisit.push(start);
    visited[start.y][start.x] = true;

    // BFS flood fill from the start tile
    while (!toVisit.empty()) {
        sf::Vector2i current = toVisit.front();
        toVisit.pop();

        // Check all 4 neighbours
        const std::array<sf::Vector2i, 4> neighbours = {{
            {current.x, current.y - 1},
            {current.x, current.y + 1},
            {current.x - 1, current.y},
            {current.x + 1, current.y}
        }};

        for (const auto& n : neighbours) {
            if (n.x < 0 || n.x >= width || n.y < 0 || n.y >= height) continue;
            if (visited[n.y][n.x]) continue;
            if (room.getTile(n.x, n.y) != FLOOR) continue;

            visited[n.y][n.x] = true;
            toVisit.push(n);
        }
    }

    // Any floor tile not reached by the fill gets converted back to a wall
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (room.getTile(x, y) == FLOOR && !visited[y][x]) {
                room.setTile(x, y, WALL);
            }
        }
    }
}