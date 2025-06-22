#pragma once
#include <string>
#include <vector>

class Room {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> exits;
    std::vector<std::string> enemies;
    bool is_locked;

    Room(std::string name, std::string desc, bool locked = false);
    void addExit(const std::string& exit);
    void addItem(const std::string& item);
    void addEnemy(const std::string& enemy);
};