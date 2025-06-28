#include "Room.h"
#include <iostream>

Room::Room(std::string name, std::string desc, int floor)
    : name(name), description(desc), floor(floor) {}

void Room::addItem(const std::string& item) {
    items.push_back(item);
}

void Room::addEnemy(const std::string& enemy) {
    enemies.push_back(enemy);
}

void Room::addInteractables(const std::string& interactable, const std::string& interactable_description) {
    interactables.push_back(interactable);
    interactables_description.push_back(interactable_description);
}

void Room::getInteractables()
{
    std::cout << "В аудитории находятся: \n";
    for (const std::string interactable : interactables) {
        std::cout << interactable << "\n";
    }
}
