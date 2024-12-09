#include "Options.h"
#include "City.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include <Windows.h>
#include "ui/CocosGUI.h" // para usar Slider

USING_NS_CC;

Scene* Options::createScene()
{
    return Options::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// Definir el ID de la música de fondo y una variable de volumen
int Options::backgroundMusicId = -1;
float Options::globalVolume = cocos2d::UserDefault::getInstance()->getFloatForKey("globalVolume", 0.5f);


// on "init" you need to initialize your instance
bool Options::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // Código para agregar la imagen de fondo
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite, 0);

    // Iniciar la música de fondo y guardar su ID
    backgroundMusicId = cocos2d::AudioEngine::play2d("ThemeSongunder.mp3", true); // true para reproducción en bucle


    // Botón de cierre en la esquina 
    auto closeItem = MenuItemImage::create(
        "BackNormal.png",
        "BackSelected.png",
        [](Ref* sender) {
            // Detener la música de fondo al regresar a la escena HelloWorld
            if (Options::backgroundMusicId != -1) {
                cocos2d::AudioEngine::stop(Options::backgroundMusicId);
                Options::backgroundMusicId = -1; // Restablecer el ID
            }

            // Reproducir sonido al presionar el botón
            cocos2d::AudioEngine::play2d("ButtonSound01.mp3", false); // false para que no se repita en bucle

            // Callback para regresar a la escena HelloWorldScene
            auto helloWorldScene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, helloWorldScene));
        });

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        closeItem->setScale(1.5f); // Ajusta el tamaño del botón si es necesario

        // Obtener el tamaño del botón después de redimensionarlo
        float width = closeItem->getContentSize().width * closeItem->getScale();
        float height = closeItem->getContentSize().height * closeItem->getScale();

        float x = origin.x + visibleSize.width - width / 2;
        float y = origin.y + height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // Crear el botón de maximizar la ventana sin cambiar a pantalla completa
    auto maximizeWindowItem = MenuItemImage::create(
        "MaxWinNormal.png",
        "MaxWinSelected.png",
        [](Ref* sender) {
            auto glView = Director::getInstance()->getOpenGLView();
            if (glView)
            {
                HWND hwnd = glView->getWin32Window();  // Obtener el manejador de ventana de Windows
                ShowWindow(hwnd, SW_MAXIMIZE);         // Maximizar la ventana como una ventana normal de Windows
            }
        });
    maximizeWindowItem->setScale(1.5f);
    maximizeWindowItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 80)); // Posición centrada y separado 25px arriba del centro

    // Crear el botón para restaurar el tamaño de la ventana
    auto restoreWindowItem = MenuItemImage::create(
        "720Normal.png",
        "720Selected.png",
        [](Ref* sender) {
            auto glView = Director::getInstance()->getOpenGLView();
            if (glView)
            {
                HWND hwnd = glView->getWin32Window();  // Obtener el manejador de ventana de Windows
                ShowWindow(hwnd, SW_RESTORE);          // Restaurar la ventana a su tamaño original
            }
        });
    restoreWindowItem->setScale(1.5f);
    restoreWindowItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 25 - 80)); // Separado 50px debajo de maximizeWindowItem

    // Etiqueta para el botón de restaurar ventana
    auto restoreLabel = Label::createWithTTF("Ajustar Volumen", "fonts/Marker Felt.ttf", 20);
    restoreLabel->setPosition(Vec2(restoreWindowItem->getPositionX(), restoreWindowItem->getPositionY() - 90)); // Posición debajo del botón
    this->addChild(restoreLabel, 2);

    // Crear el menú con los botones de maximizar y restaurar ventana
    auto menu = Menu::create(closeItem, maximizeWindowItem, restoreWindowItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear el slider para controlar el volumen
    auto volumeSlider = ui::Slider::create();
    volumeSlider->loadBarTexture("sliderTrack.png");        // Imagen de fondo del slider
    volumeSlider->loadSlidBallTextures("sliderThumb.png");  // Imagen del deslizador
    volumeSlider->loadProgressBarTexture("sliderProgress.png"); // Imagen del progreso

    // Cargar el volumen guardado desde UserDefault, si existe
    float savedVolume = cocos2d::UserDefault::getInstance()->getFloatForKey("globalVolume", 0.5f); // 0.5f es el valor por defecto
    Options::globalVolume = savedVolume;  // Establecer el valor globalVolume a lo que se había guardado

    // Ajustar el slider al volumen guardado
    volumeSlider->setPercent(static_cast<int>(savedVolume * 100));  // Establecer el porcentaje en el slider (0 - 100)

    // Modificar la escala del slider si es necesario
    volumeSlider->setScale(1.8f); // Ajustar la escala, puedes modificar este valor

    // Posicionar el slider debajo del botón de restaurar ventana
    volumeSlider->setPosition(Vec2(visibleSize.width / 2, restoreWindowItem->getPositionY() - 140));
    this->addChild(volumeSlider);

    // Callback para actualizar el volumen
    volumeSlider->addEventListener([](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            auto slider = dynamic_cast<ui::Slider*>(sender);
            if (slider) {
                float volume = slider->getPercent() / 100.0f;  // Convertir el porcentaje a valor entre 0.0f y 1.0f
                Options::globalVolume = volume;  // Actualizar el volumen global
                cocos2d::AudioEngine::setVolume(Options::backgroundMusicId, volume);  // Aplicar el nuevo volumen

                // Guardar el nuevo volumen en UserDefault para que se recuerde en la siguiente vez
                cocos2d::UserDefault::getInstance()->setFloatForKey("globalVolume", volume);
                cocos2d::UserDefault::getInstance()->flush(); // Asegura que se guarde inmediatamente
            }
        }
        });

    //texto hasta arriba nada por lo pronto
    auto label = Label::createWithTTF(" Options ", "fonts/Marker Felt.ttf", 24);//texto hasta arriba
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


void Options::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

