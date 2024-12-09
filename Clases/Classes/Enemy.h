#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <algorithm>
#include "cocos2d.h"

class Enemy : public cocos2d::Sprite {
public:
    static Enemy* createEnemy(const cocos2d::Vec2& position);
    //virtual ~Enemy(); // Destructor para manejar la liberaci�n de recursos
    void update(float delta);
    void initOptions();
    void initAnimations();
    void loadIdleAnimation();
    void loadWalkAnimation();
    void loadAttackAnimation();

    // Animaci�n y gesti�n de estados
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
    cocos2d::Vec2 origin;  // Posici�n original para control de movimiento aleatorio 
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> attackFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> hitFrames;
    cocos2d::Animation* idleAnimation; // Animaci�n para estar inactivo
    cocos2d::Animation* walkAnimation; // Animaci�n para caminar
    cocos2d::Animation* attackAnimation; // Animaci�n para atacar
    std::string currentAction; // Acci�n actual para control de animaciones
    
  
    bool isPlayerNear();
    void checkFlip(); //  ajustar la orientaci�n del sprite
};

#endif // __ENEMY_H__