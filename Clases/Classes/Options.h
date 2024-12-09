
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class Options : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // Añade esta variable miembro para el ID de la música de fondo
    static int backgroundMusicId;
    static float globalVolume;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // Agregar el sprite del cursor
    cocos2d::Sprite* cursorSprite;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Options);
};

#endif // __HELLOWORLD_SCENE_H__
