#include "CombatSystem.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

bool CombatSystem::fight(Player& player, Enemy& enemy) {
    while (enemy.health > 0 && player.getHealth() > 0) {

        std::ifstream file("CombatSystem.json");
        nlohmann::json data;

        file >> data;

        file.close();


        std::string chosenItem;
        while(chosenItem != "ready"){
            std::cout << data["choose_item"];
            player.showInventory();
            std::cin >> chosenItem;
            if (player.useItem(chosenItem)) {
                if (enemy.takeDamage(chosenItem)) {
                    std::cout << data["hit"] << enemy.name << " HP: " << enemy.health << "\n";
                }
                else {
                    std::cout << data["no_hit"];
                }
            }
            else {
                std::cout << data["reloud"];
            }
        }
        player.takeDamage(enemy.damage);
    }
    return enemy.health <= 0;
}