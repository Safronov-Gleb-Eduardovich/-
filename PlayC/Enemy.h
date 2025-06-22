#pragma once
#include <string>

class Enemy {
public:
    std::string name;
    std::string weakness;
    int health;

    Enemy(std::string name, std::string weakness, int health);
    bool takeDamage(const std::string& playerItem);
};