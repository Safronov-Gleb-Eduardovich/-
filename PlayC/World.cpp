#include "World.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

World::World(const std::string& filePath) {
    try {
        std::ifstream file(filePath);
        nlohmann::json data;

        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filePath);
        }

        file >> data;

        for (const auto& roomData : data["rooms"]) {
            Room room(roomData["name"], roomData["description"], roomData.value("is_locked", false));

            for (const auto& exit : roomData["exits"]) {
                room.addExit(exit);
            }

            for (const auto& item : roomData["items"]) {
                room.addItem(item);
            }

            rooms.push_back(room);
        }
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки мира: " << e.what() << std::endl;
        throw;
    }
}

Room* World::getStartRoom() {
    return &rooms[0];
}