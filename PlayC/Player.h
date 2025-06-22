#pragma once
#include "Item.h"
#include "Room.h"
#include <vector>

class Player {
private:
    Room* currentRoom;
    std::vector<Item> inventory;
    int health;
public:
    Player(Room* startRoom);
    bool move(const std::string& direction);
    void addItem(const Item& item);
    void showInventory() const;
    bool useItem(const std::string& itemName);
    void rechargeItem(const std::string& itemName, int amount);
    int getHealth() const;
    void takeDamage(int damage);
    Room* getCurrentRoom() const;
};