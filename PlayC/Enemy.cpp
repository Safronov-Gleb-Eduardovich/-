#include "Enemy.h"
#include <nlohmann/json.hpp>
#include <fstream>

Enemy::Enemy(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json data;

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filePath);
    }

    file >> data;

    name = data["name"];
    weakness = data["weakness"];
    health = data["health"];
    damage = data["damage"];

    file.close();
}

bool Enemy::takeDamage(const std::string& playerItem) {
    if (playerItem == weakness) {
        health -= 10;
        return true;
    }
    return false;
}