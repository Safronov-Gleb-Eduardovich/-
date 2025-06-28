#pragma once
#include <string>
#include <vector>

class Room {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    int floor;
    std::vector<std::string> enemies;
    std::vector<std::string> interactables;
    std::vector<std::string> interactables_description;

    Room(std::string name, std::string desc, int floor);
    void addItem(const std::string& item);
    void addEnemy(const std::string& enemy); 
    void addInteractables(const std::string& interactable, const std::string& interactable_description);
    void getInteractables();
};