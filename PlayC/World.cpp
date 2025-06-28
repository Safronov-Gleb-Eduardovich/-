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
        Room room(questRoomData["name"], questRoomData["floors"]);

        for (const auto& item : questRoomData["items"]) {
            room.addItem(item);
        }
        for (const auto& description : questRoomData["description"]) {
            room.addDescription(description);
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
        for (int N = 1; N != dist(gen)+1; N++) {
            int type = dist(gen)-1;
            Room room(data["rooms"][type]["name"], floor);
            for (const auto& item : data["rooms"][type]["items"]) {
                room.addItem(item);
            }
            for (const auto& description : data["rooms"][type]["description"]) {
                room.addDescription(description);
            }
            for (const auto& enemy : data["rooms"][type]["enemies"]) {
                room.addEnemy(enemy);
            }

            rooms[room.floor].push_back(room);
        }
    }
    
    for (int floor = 0; floor != 5; floor++) {
        Room room(data["stairs"]["name"], floor);
        rooms[floor].push_back(room);
    }
    file.close();
}

Room World::getStartRoom() {
    return rooms[0][0];
}

std::vector<Room> World::getNowFloor(int floor)
{
    return rooms[floor];
}
