#include "World.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <random>

World::World(const std::string& filePath) {
    rooms.resize(5);

    std::ifstream file(filePath);
    nlohmann::json data;

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filePath);
    }

    file >> data;

    //Создание квестовых(сюжетных) комнат
    for (const auto& questRoomData : data["quest_auditors"]) {
        Room room(questRoomData["name"], questRoomData["description"], questRoomData["floor"]);

        for (const auto& item : questRoomData["items"]) {
            room.addItem(item);
        }
        for (const auto& enemy : questRoomData["enemies"]) {
            room.addEnemy(enemy);
        }
        for (const auto& interactables : questRoomData["interactables"]) {
            room.addInteractables(interactables["type"], interactables["description"]);
        }

        rooms[room.floor].push_back(room);
    }


    //Создание аудиторий
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 3);

    for (int floor = 1; floor != 4; floor++) {
        for (int N = 1; N != dist(gen); N++) {
            int type = dist(gen);
            Room room(data["rooms"][type]["name"], data["rooms"][type]["description"], floor);
            for (const auto& item : data["rooms"][type]["items"]) {
                room.addItem(item);
            }
            for (const auto& enemy : data["rooms"][type]["enemies"]) {
                room.addEnemy(enemy);
            }

            rooms[room.floor].push_back(room);
        }
    }
    
    for (int floor = 0; floor != 5; floor++) {
        Room room(data["stairs"]["name"], data["stairs"]["description"], floor);
        rooms[floor].push_back(room);
    }
}

Room* World::getStartRoom() {
    return &rooms[0][0];
}

void World::getNowFloor(int floor)
{
    std::cout << "На этаже находятся: \n";
    for (const auto& room : rooms[floor]) {
        std::cout << room.name << "\n";
    }
}
