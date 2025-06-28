#pragma once
#include <string>

class Enemy {
public:
    std::string name;
    std::string weakness;
    int health;
    int damage;

    Enemy(const std::string& filePath);
    bool takeDamage(const std::string& playerItem);
};