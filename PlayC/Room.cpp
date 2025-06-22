#include "Room.h"

Room::Room(std::string name, std::string desc, bool locked)
    : name(name), description(desc), is_locked(locked) {}

void Room::addExit(const std::string& exit) {
    exits.push_back(exit);
}

void Room::addItem(const std::string& item) {
    items.push_back(item);
}

void Room::addEnemy(const std::string& enemy) {
    enemies.push_back(enemy);
}