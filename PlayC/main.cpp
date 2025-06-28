#include <iostream>
#include <locale>
#include "World.h"
#include "Player.h"
#include "CombatSystem.h"
#include "DialogueSystem.h"
#include <windows.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);

    World world("university_map.json");
    Player player(world.getStartRoom());
    DialogueSystem dialogues;
    dialogues.loadDialogues("dialogues.json");
    // Добавляем стартовые предметы
    player.addItem(Item("ultrasonic_remote", 5));
    player.addItem(Item("flamethrower", 10));
    player.addItem(Item("battery", 3));

    while (true) {
        // Отображение текущей комнаты
        std::cout << "--- " << player.getCurrentRoom().name << " ---\n";
        for (const auto& description : player.getCurrentRoom().descriptions) {
            std::cout << description << "\n";
        }
        
        // Проверка на врагов
        if (!player.getCurrentRoom().enemies.empty()) {
            Enemy enemy(player.getCurrentRoom().enemies[0], "flamethrower", 30);
            CombatSystem::fight(player, enemy);
        }

            // Ввод команды
        std::string command;
        std::cout << "> ";
        std::cin >> command;
        if (command == "идти") {
            std::string direction;
            std::cin >> direction;
            for (const auto& room : world.getNowFloor(player.getCurrentRoom().floor)) {
                if (direction == "Лестница") {
                    if (room.floor == 0) {
                        std::cout << "KKKK" << "\n";
                        player.changingCurrentRoom(world.getNowFloor(1)[world.getNowFloor(1).size() - 1]);
                        break;
                    }
                    else if (room.floor != 0 and room.floor != 4) {
                        std::cout << "Подняться или спуситься?\n";
                        std::cout << "> ";
                        std::cin >> command;
                        if (command == "подняться") {
                            std::cout << "Вы подымаетесь на этаж выше" << "\n";
                            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor + 1)[world.getNowFloor(player.getCurrentRoom().floor + 1).size() - 1]);
                        }
                        if (command == "спуститься") {
                            std::cout << "Вы спускаетесь на этаж ниже" << "\n";
                            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor - 1)[world.getNowFloor(player.getCurrentRoom().floor - 1).size() - 1]);
                        }
                        break;
                    }
                    else if (room.floor == 4) {
                        std::cout << "Вы спускаетесь на этаж ниже" << "\n";
                        player.changingCurrentRoom(world.getNowFloor(3)[world.getNowFloor(3).size() - 1]);
                        break;
                    }
                }
                else if (room.name == direction) {
                    player.changingCurrentRoom(room);
                }
            }
        }
        else if (command == "выйти") {
            player.changingCurrentRoom(world.getNowFloor(player.getCurrentRoom().floor)[world.getNowFloor(player.getCurrentRoom().floor).size()-1]);
        }
        else if (command == "осмотреться") {
            if (player.getCurrentRoom().name != u8"Лестница") {
                player.getCurrentRoom().getInteractables();
            }
            else {
                std::cout << "На этаже находятся: \n";
                for (const auto& room : world.getNowFloor(player.getCurrentRoom().floor)) {
                    std::cout << room.name << "\n";
                }
            }
        }
        else if (command == "инвентарь") {
            player.showInventory();
        }
        else if (command == "перезарядить") {
            std::string itemName;
            int amount;
            std::cin >> itemName >> amount;
            player.rechargeItem(itemName, amount);
        }
    }

    return 0;
}