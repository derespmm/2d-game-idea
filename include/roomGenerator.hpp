#ifndef ROOM_GENERATOR_HPP
#define ROOM_GENERATOR_HPP

#include "Room.hpp"
#include <random>

class RoomGenerator {
public:
    RoomGenerator(int targetFloors);
    void generate(Room& room);

private:
    int targetFloors;
    std::mt19937 rng; // Modern C++ random engine
};

#endif