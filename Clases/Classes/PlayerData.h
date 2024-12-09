#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <string>
#include <algorithm>  // Para std::max
#include "HUD.h"

class PlayerData {
public:
    static PlayerData* getInstance() {
        static PlayerData instance;
        return &instance;
    }

    // Métodos para acceso a las variables
    std::string getPlayerName() const { return playerName; }
    void setPlayerName(const std::string& name) { playerName = name; }

    int getPlayerLevel() const { return playerLevel; }
    void setPlayerLevel(int level) { playerLevel = level; }

    int getAttackPower() const { return playerAttack; }  // Cambiado de getPlayerAttack
    void setPlayerAttack(int attack) { playerAttack = attack; }

    int getPlayerHealth() const { return playerHealth; }
    void setPlayerHealth(int health) { playerHealth = std::max(0, health); }

    int getPlayerExperience() const { return playerExperience; }
    void addExperience(int exp) {  // Cambiado de addPlayerExperience
        playerExperience += exp;
        checkLevelUp();
    }

    int getPlayerGold() const { return playerGold; }
    void addGold(int gold) { playerGold += gold; }  // Cambiado de addPlayerGold

private:
    // Constructor privado
    PlayerData() : playerName("Vel"), playerLevel(1), playerAttack(20), playerHealth(100), playerExperience(0), playerGold(0) {}

    // Variables del jugador
    std::string playerName;
    int playerLevel;
    int playerAttack;
    int playerHealth;
    int playerExperience;
    int playerGold;

    // Método para comprobar y gestionar la subida de nivel
    void checkLevelUp() {
        int xpNeeded = playerLevel * 100; // Por ejemplo, 100 XP por nivel
        while (playerExperience >= xpNeeded) {
            playerLevel++;
            playerExperience -= xpNeeded;
            levelUp();
            xpNeeded = playerLevel * 100;  // Actualiza la experiencia necesaria para el siguiente nivel
        }
    }

    // Método para gestionar el efecto de subir de nivel
    void levelUp() {
        playerHealth += 20;  // Aumenta la salud máxima
        playerAttack += 5;   // Aumenta el poder de ataque
    }
};

#endif // PLAYER_DATA_H