#include "CombatSystem.h"
#include <iostream>

bool CombatSystem::fight(Player& player, Enemy& enemy) {
    while (enemy.health > 0 && player.getHealth() > 0) {
        player.showInventory();
        std::cout << "Выберите предмет для атаки: ";

        std::string chosenItem;
        std::cin >> chosenItem;

        if (player.useItem(chosenItem)) {
            if (enemy.takeDamage(chosenItem)) {
                std::cout << "Попадание! " << enemy.name << " HP: " << enemy.health << "\n";
            }
            else {
                std::cout << "Неэффективно! ";
            }
        }
        else {
            std::cout << "Недостаточно зарядов или предмета!\n";
        }
    }
    return enemy.health <= 0;
}