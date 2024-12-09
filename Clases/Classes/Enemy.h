#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <algorithm>
#include "cocos2d.h"

class Enemy : public cocos2d::Sprite {
public:
    static Enemy* createEnemy(const cocos2d::Vec2& position);
    //virtual ~Enemy(); // Destructor para manejar la liberación de recursos
    void update(float delta);
    void initOptions();
    void initAnimations();
    void loadIdleAnimation();
    void loadWalkAnimation();
    void loadAttackAnimation();

    // Animación y gestión de estados
    void idle();
    void walk();
    void attack();
    void hit();
    void setPlayerReference(cocos2d::Node* player);

private:
    int level;
    int attackPower;
    int health;
    cocos2d::Node* player; // Referencia al jugador
    cocos2d::Vec2 origin;  // Posición original para control de movimiento aleatorio 
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> attackFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> hitFrames;
    cocos2d::Animation* idleAnimation; // Animación para estar inactivo
    cocos2d::Animation* walkAnimation; // Animación para caminar
    cocos2d::Animation* attackAnimation; // Animación para atacar
    std::string currentAction; // Acción actual para control de animaciones
    
  
    bool isPlayerNear();
    void checkFlip(); //  ajustar la orientación del sprite
};

#endif // __ENEMY_H__