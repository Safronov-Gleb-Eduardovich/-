#pragma once
#include "Room.h"
#include <vector>
#include <string>

class World {
private:
    std::vector<std::vector<Room>> rooms;
public:
    World(const std::string& filePath);
    Room* getStartRoom();
    void getNowFloor(int floor);
};