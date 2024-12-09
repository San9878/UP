// Combat.h
#ifndef COMBAT_H
#define COMBAT_H

#include "PlayerData.h"
#include <algorithm>
#include "cocos2d.h"
#include "Character.h"
#include "Enemy.h"

class Combat {
public:
    static void performAttack(Enemy* attacker, PlayerData* defender);
    static void handleLootDrop(PlayerData* player);

private:
    Combat(); // Constructor privado para prevenir instanciación
};

#endif // COMBAT_H
