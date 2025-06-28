#include <iostream>
#include <locale>
#include "World.h"
#include "Player.h"
#include "CombatSystem.h"
#include "DialogueSystem.h"
#include <windows.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(1251);
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
        std::cout << "--- " << player.getCurrentRoom()->name << " ---\n";
        std::cout << player.getCurrentRoom()->description << "\n";

        // Проверка на врагов
        if (!player.getCurrentRoom()->enemies.empty()) {
            Enemy enemy(player.getCurrentRoom()->enemies[0], "flamethrower", 30);
            CombatSystem::fight(player, enemy);
        }

            // Ввод команды
        std::string command;
        std::cout << "> ";
        std::cin >> command;
        /*if (command == "идти") {
            std::string direction;
            std::cin >> direction;
            player.move(direction);
        }*/
        //else 
        if (command == "осмотреться") {
            if (player.getCurrentRoom()->name != "Лестница") {
                player.getCurrentRoom()->getInteractables();
            }
            else {
                world.getNowFloor(player.getCurrentRoom()->floor);
            }
            player.showInventory();
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