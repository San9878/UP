#include "HUD.h"
#include "PlayerData.h"

HUD* HUD::createWithPlayer(cocos2d::Node* player) {
    HUD* hud = new (std::nothrow) HUD();
    if (hud && hud->initWithPlayer(player)) {
        hud->autorelease();
        return hud;
    }
    CC_SAFE_DELETE(hud);
    return nullptr;
}

bool HUD::initWithPlayer(cocos2d::Node* player) {
    if (!Node::init()) {
        return false;
    }

    this->player = player;  // Guarda la referencia al jugador

    // Crear y configurar las etiquetas
    healthLabel = cocos2d::Label::createWithTTF("Health: 20 ", "fonts/Marker Felt.ttf", 24);
    levelLabel = cocos2d::Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 24);

    // Posicionar las etiquetas en el HUD
    healthLabel->setPosition(cocos2d::Vec2(50, 25));  // Ajusta estas posiciones según tus necesidades
    levelLabel->setPosition(cocos2d::Vec2(50, 50));

    this->addChild(healthLabel);
    this->addChild(levelLabel);

    this->scheduleUpdate();  // Asegúrate de que update se llame cada frame

    return true;
}

void HUD::update(float delta) {
    if (player) {
        // Asegúrate de que el HUD sigue al jugador
        this->setPosition(player->getPosition() + cocos2d::Vec2(0, 50));  // Ajusta según la UI

        // Actualizar las etiquetas
        auto playerData = PlayerData::getInstance();
        healthLabel->setString("Health: " + std::to_string(playerData->getPlayerHealth()));
        levelLabel->setString("Level: " + std::to_string(playerData->getPlayerLevel()));
    }
}
