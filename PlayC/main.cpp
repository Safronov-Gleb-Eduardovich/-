#include <iostream>
#include <locale>
#include "World.h"
#include "Player.h"
#include "CombatSystem.h"
#include "DialogueSystem.h"
#include <windows.h>
#include <nlohmann/json.hpp>
#include <fstream>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);

    std::ifstream file("move.json");
    nlohmann::json move;

    file >> move;

    file.close();

    World world("university_map.json");
    Player player(world.getStartRoom());
    DialogueSystem dialogues;
    dialogues.loadDialogues("dialogues.json");
   

    while (true) {
        // Отображение текущей комнаты
        std::cout << "--- " << player.getCurrentRoom().name << " ---\n";
        for (const auto& description : player.getCurrentRoom().descriptions) {
            std::cout << description << "\n";
        }
        
        // Проверка на врагов
        if (!player.getCurrentRoom().enemies.empty()) {
            for (const auto enemy : player.getCurrentRoom().enemies){
                Enemy enemy("enemy.json");
                if (!CombatSystem::fight(player, enemy)) { 
                    std::cout << move["death"];
                    return 0;
                };
            }
        }

            // Ввод команды
        std::string command;
        std::cout << "> ";
        std::cin >> command;
        if (command == move["go"]) {
            std::string direction;
            std::cin >> direction;
            for (const auto& room : world.getNowFloor(player.getCurrentRoom().floor)) {
                if (direction == "stairs") {
                    if (room.floor == 0) {
                        player.changingCurrentRoom(world.getNowFloor(1)[world.getNowFloor(1).size() - 1]);
                        break;
                    }
                    else if (room.floor != 0 and room.floor != 4) {
                        std::cout << "> ";
                        std::cin >> command;
                        if (command == move["go up"]) {
                            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor + 1)[world.getNowFloor(player.getCurrentRoom().floor + 1).size() - 1]);
                        }
                        if (command == move["go down"]) {
                            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor - 1)[world.getNowFloor(player.getCurrentRoom().floor - 1).size() - 1]);
                        }
                        break;
                    }
                    else if (room.floor == 4) {
                        player.changingCurrentRoom(world.getNowFloor(3)[world.getNowFloor(3).size() - 1]);
                        break;
                    }
                }
                else if (room.name == direction) {
                    player.changingCurrentRoom(room);
                }
            }
        }
        else if (command == move["go out"]) {
            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor)[world.getNowFloor(player.getCurrentRoom().floor).size()-1]);
        }
        else if (command == move["look around"]) {
            if (player.getCurrentRoom().name != "stairs") {
                player.getCurrentRoom().getInteractables();
            }
            else {
                for (const auto& room : world.getNowFloor(player.getCurrentRoom().floor)) {
                    std::cout << room.name << "\n";
                }
            }
        }
        else if (command == move["inventory"]) {
            player.showInventory();
        }
        else if (command == move["reload"]) {
            std::string itemName;
            int amount;
            std::cin >> itemName >> amount;
            player.rechargeItem(itemName, amount);
        }
    }

    return 0;
}