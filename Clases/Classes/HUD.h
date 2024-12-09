#ifndef HUD_H
#define HUD_H

#include "cocos2d.h"
#include "PlayerData.h"  // Asegúrate de incluir esto si necesitas acceder a los datos del jugador
#include "City.h"

class HUD : public cocos2d::Node {
public:
    static HUD* createWithPlayer(cocos2d::Node* player);
    virtual bool initWithPlayer(cocos2d::Node* player);
    void update(float delta);

private:
    cocos2d::Node* player;  // Referencia al jugador
    cocos2d::Label* healthLabel;
    cocos2d::Label* levelLabel;
};

#endif // HUD_H