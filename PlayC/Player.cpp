#include "Player.h"
#include <iostream>

Player::Player(Room* startRoom) : currentRoom(startRoom), health(100) {}

//bool Player::move(const std::string& direction) {
//    for (const auto& exit : currentRoom.floor) {
//        if (exit == direction) {
//            // ������ �������� � ������ �������
//            return true;
//        }
//    }
//    std::cout << "���� ������ ������!\n";
//    return false;
//}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

void Player::showInventory() const {
    std::cout << "���������:\n";
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
            std::cout << itemName << " �����������!\n";
            return;
        }
    }
    std::cout << "������� �� ������.\n";
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