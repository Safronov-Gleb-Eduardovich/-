#include <iostream>
#include <locale>
#include "World.h"
#include "Player.h"
#include "CombatSystem.h"
#include "DialogueSystem.h"

int main() {
    std::locale::global(std::locale{ ".UTF-8" });
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    try {
        World world("university_map.json");
        Player player(world.getStartRoom());

        DialogueSystem dialogues;
        try {
            dialogues.loadDialogues("dialogues.json");
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка загрузки диалогов: " << e.what() << std::endl;
        }

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

            if (command == "идти") {
                std::string direction;
                std::cin >> direction;
                player.move(direction);
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
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}