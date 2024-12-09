#include "Combat.h"
#include "Enemy.h"
#include "PlayerData.h"
#include <algorithm>  // Incluir para std::max
#include "Character.h"
/*
void Combat::attack(Character* attacker, Character* defender) {
    // Calcula el daño básico como la diferencia entre el ataque del atacante y la defensa del defensor
    int baseDamage = attacker->getAttackPower() - defender->getDefense();

    // Asegura que el daño no sea negativo usando std::max
    int damage = std::max(0, baseDamage);  // Asegúrate de que ambos argumentos sean enteros

    // Aplica el daño al defensor
    defender->setHealth(defender->getHealth() - damage);

    // Si el defensor es un enemigo y su salud cae a 0 o menos, maneja su muerte
    if (defender->getHealth() <= 0) {
        handleDeath(defender);
    }
}

void Combat::handleDeath(Character* character) {
    if (character->getType() == CharacterType::Enemy) {
        // Suma experiencia y oro al jugador
        PlayerData::getInstance()->addExperience(50);  // Por ejemplo, añade 50 puntos de experiencia
        PlayerData::getInstance()->addGold(rand() % 5 + 1);  // Añade entre 1 y 5 monedas de oro de manera aleatoria
    }
}*/