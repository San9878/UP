/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include "City.h"
#include "Options.h"

USING_NS_CC;


// Variable de clase para almacenar el ID de la música
int HelloWorld::backgroundMusicId = -1;



Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Oculta el cursor estándar del sistema
    Director::getInstance()->getOpenGLView()->setCursorVisible(false);

    // Iniciar la música de fondo y establecer el volumen global
    backgroundMusicId = cocos2d::AudioEngine::play2d("ThemeSong.mp3", true);  // true para reproducir en bucle
    cocos2d::AudioEngine::setVolume(backgroundMusicId, Options::globalVolume);  // Aplicar el volumen global al audio


    // Código para agregar la imagen de fondo
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite, 0);

 
    //"The dark dungeon"
    auto titleLabel = Label::createWithTTF("The dark Dungeon", "fonts/Marker Felt.ttf", 100); // tamaño de fuente 
    if (titleLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // establece el color del texto
        titleLabel->setTextColor(Color4B(180, 4, 4, 255)); // color en hexadecimal convertido  #B40404

        // centra el título en el medio de la pantalla
        titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));

        // añade el título a la escena
        this->addChild(titleLabel, 1);
    }

    // "By: Santiago Hernandez Chavez"
    auto subtitleLabel = Label::createWithTTF("By: Santiago Hernandez Chavez", "fonts/Marker Felt.ttf", 30); // tamaño de fuente 
    if (subtitleLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // establece el color del texto en blanco
        subtitleLabel->setTextColor(Color4B::WHITE);

        // centra el subtítulo debajo del título
        subtitleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 10));

        // añade el subtítulo a la escena
        this->addChild(subtitleLabel, 1);
    }

    // Botones
   // Boton cerrar
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        closeItem->setScale(1.5f); //tamaño

        // Obtener el tamaño del botón después de redimensionarlo
        float width = closeItem->getContentSize().width * closeItem->getScale();
        float height = closeItem->getContentSize().height * closeItem->getScale();

        // Posicionar el botón en la esquina superior derecha de la pantalla
        float x = origin.x + visibleSize.width - width / 2;
        float y = origin.y + height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // Botón de inicio (con acción y sonido)
    auto startItem = MenuItemImage::create(
        "StartNormal.png",   // Imagen normal
        "StartSelected.png", // Imagen seleccionada
        [](Ref* sender) {
            // Detener la música de fondo antes de cambiar de escena
            if (HelloWorld::backgroundMusicId != -1) {
                cocos2d::AudioEngine::stop(HelloWorld::backgroundMusicId);
                HelloWorld::backgroundMusicId = -1; // Restablecer el ID
            }

            // Reproducir sonido al presionar el botón
            cocos2d::AudioEngine::play2d("ButtonSound01.mp3", false); // false para que no se repita en bucle

            // Cambiar a la escena City
            auto cityScene = City::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, cityScene)); // Transición de desvanecimiento
        });

            if (startItem == nullptr ||
                startItem->getContentSize().width <= 0 ||
                startItem->getContentSize().height <= 0)
            {
                problemLoading("'StartNormal.png' and 'StartSelected.png'");
            }
            else
            {
                startItem->setScale(1.5f); // tamaño

                float x = visibleSize.width / 2 + origin.x;
                float y = visibleSize.height / 2 + origin.y - closeItem->getContentSize().height / 2 - 50; // 50 es el margen debajo de la imagen
                startItem->setPosition(Vec2(x, y));
            }

    // Botón de opciones (con acción y sonido)
    auto OptionsItem = MenuItemImage::create(
        "OptionsNormal.png",
        "OptionsSelected.png",
        [](Ref* sender) {
            // Detener la música de fondo antes de cambiar de escena
            if (HelloWorld::backgroundMusicId != -1) {
                cocos2d::AudioEngine::stop(HelloWorld::backgroundMusicId);
                HelloWorld::backgroundMusicId = -1; // Restablecer el ID
            }

            // Reproducir sonido al presionar el botón
            cocos2d::AudioEngine::play2d("ButtonSound01.mp3", false); // false para que no se repita en bucle

            // Cambiar a la escena Options
            auto optionsScene = Options::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, optionsScene)); // Transición de desvanecimiento
        });
            if (OptionsItem == nullptr ||
                OptionsItem->getContentSize().width <= 0 ||
                OptionsItem->getContentSize().height <= 0)
            {
                problemLoading("'OptionsNormal.png' and 'OptionsSelected.png'");
            }
            else
            {
                OptionsItem->setScale(0.5f); //tamaño

                // Posicionar el botón OptionsItem en la esquina superior derecha, alineado horizontalmente con closeItem
                float x = origin.x + visibleSize.width - OptionsItem->getContentSize().width / 2 - 10;  // margen derecho de 10
                float y = origin.y + visibleSize.height - OptionsItem->getContentSize().height / 2 - 10; // margen superior de 10
                OptionsItem->setPosition(Vec2(x, y));
            }



    // Crear el menú y agregar los botones, con un z-order alto para que esté al frente
    auto menu = Menu::create(closeItem, startItem, OptionsItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10); // Z-order alto para asegurar que el menú esté al frente



    //texto hasta arriba nada por lo pronto
    auto label = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 24);//texto hasta arriba
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {

        sprite->setScale(0.1f);  // Esto establece el tamaño espadas

        //  centro de la pantalla
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


        this->addChild(sprite, 0);
    }


    // Crear el sprite del cursor y establecer su posición inicial
    cursorSprite = Sprite::create("MouseNormal.png");
    cursorSprite->setAnchorPoint(Vec2(0, 1)); // Ajusta el ancla del cursor para que la punta esté en la esquina superior izquierda
    cursorSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); // Posición inicial en el centro de la pantalla
    this->addChild(cursorSprite, 20); // Z-order alto para que esté al frente

    // Programar el evento de movimiento del ratón para actualizar la posición del cursor personalizado
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [this](EventMouse* event) {
        cursorSprite->setPosition(event->getCursorX(), event->getCursorY());
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this); 


    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

