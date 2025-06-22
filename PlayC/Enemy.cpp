#include "Enemy.h"

Enemy::Enemy(std::string name, std::string weakness, int health)
    : name(name), weakness(weakness), health(health) {}

bool Enemy::takeDamage(const std::string& playerItem) {
    if (playerItem == weakness) {
        health -= 10;
        return true;
    }
    return false;
}