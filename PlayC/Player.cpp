#include "Player.h"
#include <iostream>

Player::Player(Room* startRoom) : currentRoom(startRoom), health(100) {}

//bool Player::move(const std::string& direction) {
//    for (const auto& exit : currentRoom.floor) {
//        if (exit == direction) {
//            // Логика перехода в другую комнату
//            return true;
//        }
//    }
//    std::cout << "Туда нельзя пройти!\n";
//    return false;
//}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

void Player::showInventory() const {
    std::cout << "Инвентарь:\n";
    for (const auto& item : inventory) {
        std::cout << "- " << item.getName()
            << " (" << item.getCharges() << "/"
            << item.getMaxCharges() << ")\n";
    }
}

bool Player::useItem(const std::string& itemName) {
    for (auto& item : inventory) {
        if (item.getName() == itemName) {
            return item.use();
        }
    }
    return false;
}

void Player::rechargeItem(const std::string& itemName, int amount) {
    for (auto& item : inventory) {
        if (item.getName() == itemName) {
            item.recharge(amount);
            std::cout << itemName << " перезаряжен!\n";
            return;
        }
    }
    std::cout << "Предмет не найден.\n";
}

int Player::getHealth() const {
    return health;
}

void Player::takeDamage(int damage) {
    health -= damage;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}