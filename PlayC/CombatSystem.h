#pragma once
#include "Player.h"
#include "Enemy.h"

class CombatSystem {
public:
    static bool fight(Player& player, Enemy& enemy);
};