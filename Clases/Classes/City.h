#ifndef __CITY_H__
#define __CITY_H__


#include "Interiores.h"
#include "cocos2d.h"
#include "Options.h"
#include "HelloWorldScene.h"
#include "Enemy.h"
#include "HUD.h"


class City : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // Declara backgroundMusicId como est�tico
    static int backgroundMusicId;

    // Declaraci�n correcta de onKeyPressed
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // Agregar el sprite del cursor
    cocos2d::Sprite* cursorSprite;

    // M�todos para controlar al personaje
    void update(float delta) override;
    void handleKeyboard(cocos2d::EventKeyboard::KeyCode keyCode, bool isPressed);
    void handleMouse(cocos2d::EventMouse* event);

    // Estad�sticas del personaje
    std::string playerName;
    int playerLevel;
    int playerAttack;
    int playerHealth;

 

    void initPlayer();                 // Inicializar el personaje
    void initKeyboardAndMouse();       // Inicializar entrada de teclado y mouse
    void updatePlayerStats();          // Actualizar estad�sticas del jugador
    void playAttackAnimation();        // Reproducir animaci�n de ataque

    bool checkCollision(int x, int y); // Funci�n para comprobar colisiones
    void checkEvent(const cocos2d::Vec2& position);

    // Implementa el "static create()" method manually
    CREATE_FUNC(City);

private:

    // Dimensiones y arreglo de la cuadr�cula
    static const int tileSize = (64);
    static const int gridWidth = (23); // alto
    static const int gridHeight = (23); // largo 

    cocos2d::Sprite* grid[gridWidth][gridHeight]; // Debe ser un puntero para almacenar objetos Sprite.
    int yOffset = -30;  // Ajuste vertical inicial

    cocos2d::Sprite* player;  // Sprite del personaje
    cocos2d::Label* statsLabel;  // Etiqueta para mostrar estad�sticas del jugador

    cocos2d::Vector<cocos2d::SpriteFrame*> runFrames; // Fotogramas para la animaci�n de correr
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames; // Fotogramas para la animaci�n de estar inactivo
    cocos2d::Vector<cocos2d::SpriteFrame*> attackFrames; // Fotogramas para la animaci�n de ataque

    cocos2d::Animate* runAnimation; // Animaci�n de correr
    cocos2d::Animate* idleAnimation; // Animaci�n de estar inactivo
    cocos2d::Animate* attackAnimation; // Animaci�n de ataque


    // Estados del teclado
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

    // Control de animaciones
    bool isAttacking; // Indica si el personaje est� atacando

    // Direcci�n del personaje
    bool facingRight;

    


};

#endif // __CITY_H__