

#include "Interiores.h"
#include "DFloor01.h"
#include "City.h"
#include "HelloWorldScene.h"
#include "Options.h"
#include "audio/include/AudioEngine.h"
#include "PlayerData.h"
#include "Enemy.h"
#include "HUD.h"

USING_NS_CC;

int City::backgroundMusicId = -1; // para volumen


Scene* City::createScene()
{
    return City::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool City::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize() * 3; // Doble de grande
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Iniciar la música de fondo y establecer el volumen global
    backgroundMusicId = cocos2d::AudioEngine::play2d("City.mp3", true);  // true para reproducir en bucle
    cocos2d::AudioEngine::setVolume(backgroundMusicId, Options::globalVolume);  // Aplicar el volumen global al audio

    // Código para agregar la imagen de fondo
    auto backgroundSprite = Sprite::create("Citybackground.jpg");
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScale(2); // Asegúrate de que el fondo cubra la nueva área ampliada
    this->addChild(backgroundSprite, 0);

    // Asumiendo que `player` es el nodo del jugador ya creado y añadido a la escena
    auto player = this->getPlayer();  // Asumiendo que tienes un método para obtener el jugador 
    auto hud = HUD::createWithPlayer(player); 
    this->addChild(hud); 


    //-------------------------------------------------------------------------- C U A D R I C U L A --------------------------------------------------------------------------------------------

    // Crear la cuadrícula
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {

            // Crear un sprite para cada celda con una textura inicial de "stone.jpg"
            grid[x][y] = Sprite::create("grass.jpg");
            grid[x][y]->setPosition(x * tileSize + origin.x + tileSize / 2, y * tileSize + origin.y + tileSize / 2 + yOffset);

            // Obtener el tamaño original de la textura
            auto textureSize = grid[x][y]->getTexture()->getContentSize();

            // Calcular la escala necesaria para ajustar la textura al tamaño de la celda
            float scaleX = tileSize / textureSize.width;
            float scaleY = tileSize / textureSize.height;
            grid[x][y]->setScale(scaleX, scaleY); // Escala la textura para que se ajuste a la celda

            this->addChild(grid[x][y]);

        }
    }

    // ----------------------------------------------------------------------------A L T O  D E R E C H A ------------------------------------------------------------------------------

    // 0 1
    grid[0][1]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][1]->setTag(1);  // Indica colisión
    // 0 2
    grid[0][2]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][2]->setTag(1);
    // 0 3
    grid[0][3]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][3]->setTag(1);
    // 0 4
    grid[0][4]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][4]->setTag(1);
    // 0 5
    grid[0][5]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][5]->setTag(1);
    // 0 6
    grid[0][6]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][6]->setTag(1);  // Indica colisión
    // 0 7
    grid[0][7]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][7]->setTag(1);
    // 0 8
    grid[0][8]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][8]->setTag(1);
    // 0 9
    grid[0][9]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][9]->setTag(1);
    // 0 10
    grid[0][10]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][10]->setTag(1);
    // 0 11
    grid[0][11]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][11]->setTag(1);  // Indica colisión
    // 0 12
    grid[0][12]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][12]->setTag(1);
    // 0 13
    grid[0][13]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][13]->setTag(1);
    // 0 14
    grid[0][14]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][14]->setTag(1);
    // 0 15
    grid[0][15]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][15]->setTag(1);
    // 0 16
    grid[0][16]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][16]->setTag(1);  // Indica colisión
    // 0 17
    grid[0][17]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][17]->setTag(1);
    // 0 18
    grid[0][18]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][18]->setTag(1);
    // 0 19
    grid[0][19]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][19]->setTag(1);
    // 0 20
    grid[0][20]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][20]->setTag(1);
    // 0 21
    grid[0][21]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][21]->setTag(1);
    // 0 22
    grid[0][22]->setTexture("wall_IZ.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][22]->setTag(1);
    // ----------------------------------------------------------------------------L A R G O ------------------------------------------------------------------------------

    // 1 0
    grid[1][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[1][0]->setTag(1);  // No colisión
    // 2 0
    grid[2][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[2][0]->setTag(1);   // No colisión
    // 3 0
    grid[3][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[3][0]->setTag(1);   // No colisión
    // 4 0
    grid[4][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[4][0]->setTag(1);  // No colisión
    // 5 0
    grid[5][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[5][0]->setTag(1);  // No colisión
    // 6 0
    grid[6][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[6][0]->setTag(1);  // No colisión
    // 7 0
    grid[7][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[7][0]->setTag(1);  // No colisión
    // 8 0
    grid[8][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[8][0]->setTag(1);  // No colisión
    // 9 0
    grid[9][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[9][0]->setTag(1);  // No colisión
    // 10 0
    grid[10][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[10][0]->setTag(1);  // No colisión
    // 11 0
    grid[11][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[11][0]->setTag(1);  // No colisión
    // 12 0
    grid[12][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[12][0]->setTag(1);  // No colisión
    // 13 0
    grid[13][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[13][0]->setTag(1);  // No colisión
    // 14 0
    grid[14][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[14][0]->setTag(1);  // No colisión
    // 15 0
    grid[15][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[15][0]->setTag(1);  // No colisión
    // 16 0
    grid[16][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[16][0]->setTag(1);  // No colisión
    // 17 0
    grid[17][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[17][0]->setTag(1);  // No colisión
    // 18 0
    grid[18][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[18][0]->setTag(1);  // No colisión
    // 19 0
    grid[19][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[19][0]->setTag(1);  // No colisión
    // 20 0
    grid[20][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[20][0]->setTag(1);  // No colisión
    // 21 0
    grid[21][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[21][0]->setTag(1);  // No colisión
    // 22 0
    grid[22][0]->setTexture("wall_Abajo.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][0]->setTag(1);  // No colisión
  


    //----------------------------------------------------------- A L T O     B O R D E --------------------------------------------------------------------------------------------------------------------

       // 1 22
    grid[1][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[1][22]->setTag(1);  // No colisión
    // 2 22
    grid[2][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[2][22]->setTag(1);  // No colisión
    // 3 22
    grid[3][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[3][22]->setTag(1);  // No colisión
    // 4 22
    grid[4][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[4][22]->setTag(1);  // No colisión
    // 5 22
    grid[5][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[5][22]->setTag(1);  // No colisión
    // 6 22
    grid[6][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[6][22]->setTag(1);  // No colisión
    // 7 22
    grid[7][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[7][22]->setTag(1);  // No colisión
    // 8 22
    grid[8][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[8][22]->setTag(1);  // No colisión
    // 9 22
    grid[9][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[9][22]->setTag(1);  // No colisión
    // 10 22
    grid[10][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[10][22]->setTag(1);  // No colisión
    // 11 22
    grid[11][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[11][22]->setTag(1);  // No colisión
    // 12 22
    grid[12][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[12][22]->setTag(1);  // No colisión
    // 13 22
    grid[13][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[13][22]->setTag(1);  // No colisión
    // 14 22
    grid[14][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[14][22]->setTag(1);  // No colisión
    // 15 22
    grid[15][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[15][22]->setTag(1);  // No colisión
    // 16 22
    grid[16][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[16][22]->setTag(1);  // No colisión
    // 17 22
    grid[17][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[17][22]->setTag(1);  // No colisión
    // 18 22
    grid[18][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[18][22]->setTag(1);  // No colisión
    // 19 22
    grid[19][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[19][22]->setTag(1);  // No colisión
    // 20 22
    grid[20][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[20][22]->setTag(1);  // No colisión
    // 21 22
    grid[21][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[21][22]->setTag(1);  // No colisión
    // 22 22
    grid[22][22]->setTexture("Wall.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][22]->setTag(1);  // No colisión
   


    //-------------------------- lado IZ --------------------------------------------------------------------------------------------------------------------
     // 40 1
    grid[22][1]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][1]->setTag(1);  // Indica colisión
    // 40 2
    grid[22][2]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][2]->setTag(1);  // No colisión
    // 40 3
    grid[22][3]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][3]->setTag(1);  // No colisión
    // 40 4
    grid[22][4]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][4]->setTag(1);  // No colisión
    // 40 5
    grid[22][5]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][5]->setTag(1);  // No colisión
    // 40 6
    grid[22][6]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][6]->setTag(1);  // Indica colisión
    // 40 7
    grid[22][7]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][7]->setTag(1);  // No colisión
    // 40 8
    grid[22][8]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][8]->setTag(1);  // No colisión
    // 40 9
    grid[22][9]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][9]->setTag(1);  // No colisión
    // 40 10
    grid[22][10]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][10]->setTag(1);  // No colisión
    // 40 11
    grid[22][11]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][11]->setTag(1);  // Indica colisión
    // 40 12
    grid[22][12]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][12]->setTag(1);  // No colisión
    // 40 13
    grid[22][13]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][13]->setTag(1);  // No colisión
    // 40 14
    grid[22][14]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][14]->setTag(1);  // No colisión
    // 40 15
    grid[22][15]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][15]->setTag(1);  // No colisión
    // 40 16
    grid[22][16]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][16]->setTag(1);  // Indica colisión
    // 40 17
    grid[22][17]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][17]->setTag(1);  // No colisión
    // 40 18
    grid[22][18]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][18]->setTag(1);  // No colisión
    // 40 19
    grid[22][19]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][19]->setTag(1);  // No colisión
    // 40 20
    grid[22][20]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][20]->setTag(1);  // No colisión
    // 40 21
    grid[22][21]->setTexture("wall_ID.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][21]->setTag(1);  // No colisión

   

    //------------------------------------------------------------ E S Q U I N A S --------------------------------------------------------------------------------------------------

    // 0 0
    grid[0][0]->setTexture("stone.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][0]->setTag(0);  // Indica colisión

    // 40 0
    grid[22][0]->setTexture("stone.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][0]->setTag(0);  // Indica colisión

    // 0 22
    grid[0][22]->setTexture("stone.jpg"); // Cambia la textura de la celda en la posición 
    grid[0][22]->setTag(0);  // Indica colisión

    // 22 40
    grid[22][22]->setTexture("stone.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][22]->setTag(0);  // Indica colisión


    //------------------------------------------------------------ R E L L E N O    I M P O R T A N T E  --------------------------------------------------------------------------------------------------
        // tienda 01
    grid[5][5]->setTexture("grass_St.jpg"); // Cambia la textura de la celda en la posición 
    //grid[5][5]->setTag(1);  //  colision
    grid[5][5]->setTag(3);  //  cambio a Interiores

    //Dungeon
    grid[22][7]->setTexture("BadPuertagrass.jpg"); // Cambia la textura de la celda en la posición 
    grid[22][7]->setTag(1);  //  colision
    grid[22][7]->setTag(4);  //  cambio a Interiores

    
    


    //----------------------------------------------------------- M O V E R S E --------------------------------------------------------------------------------------------------------
        // para moverse wasd
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        this->keys[keyCode] = true;
        };
    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        this->keys[keyCode] = false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    //----------------------------------------------------- C R E A R  P E R S O N A J E --------------------------------------------------------------------------------------
    // Crear el personaje jugable
    initPlayer();
 

    // Crear el EventListenerKeyboard para la tecla ESC
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(City::onKeyPressed, this); // Enlazar el método a onKeyPressed
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //-------------------------- Para el cursor y el mouse interno ----------------------------------------------------------------------------------------------------------

    // Cursor sprite setup
    cursorSprite = Sprite::create("MouseNormal.png");
    cursorSprite->setAnchorPoint(Vec2(0, 1));  // Anchor point set to the top-left corner
    cursorSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);  // Initial position at the center of the screen
    cursorSprite->setScale(0.3f);

    // Create a node that stays fixed relative to the screen, not the world
    auto fixedNode = Node::create();
    fixedNode->setPosition(Vec2::ZERO);
    this->addChild(fixedNode, 30);  // Higher z-order to ensure it is above everything else


    // Add the cursor to the fixed node, ensuring it doesn't move with the world
    fixedNode->addChild(cursorSprite);


    // Event listener for moving the cursor, this moves the cursor within the fixed node
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [this, fixedNode](EventMouse* event) {
        auto winSize = Director::getInstance()->getVisibleSize();
        fixedNode->setPosition(Director::getInstance()->getVisibleOrigin()); // Adjust the fixed node's position to always align with the viewport
        cursorSprite->setPosition(event->getCursorX() - fixedNode->getPositionX(), event->getCursorY() - fixedNode->getPositionY());
        };

    // Adding the mouse listener to handle mouse click for attacking
    mouseListener->onMouseDown = [this](EventMouse* event) {
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            playAttackAnimation();  // Assuming this function handles the attack animation
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, fixedNode);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Schedule update to handle movements and other frame updates
    this->scheduleUpdate();

    //--------------------------------------------- T O P    T E X T ----------------------------------------------------------------------------------------------------
    // Texto hasta arriba (si es necesario)
    auto label = Label::createWithTTF("  ", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // Position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // Add the label as a child to this layer
        this->addChild(label, 1);
    }
    return true;
}

//---------------------------------------------------------------------- T E C L A   E S C -------------------------------------------------------------------------------------------
// Función para detectar la tecla ESC
void City::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        // Detener la música de fondo
        if (City::backgroundMusicId != -1) {
            cocos2d::AudioEngine::stop(City::backgroundMusicId);
            City::backgroundMusicId = -1;
        }

        // Reproducir sonido al presionar el botón
        cocos2d::AudioEngine::play2d("ButtonSound01.mp3", false);

        // Cambiar a la escena de opciones
        auto optionsScene = Options::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, optionsScene));
    }
}


//------------------------------------------------------- M E N U    C L O S E ------------------------------------------------------------------------------------------
void City::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


    

// ----------------------------------------------------------------- I N   P E R S O N A J E-------------------------------------------------------------------------------------
// Inicializar al jugador y sus estadísticas
void City::initPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Cargar los fotogramas de animación para correr
    auto cache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 8; ++i) {
        std::string frameName = "Warrior_Run_" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64));
        if (frame == nullptr) {
            log("Error: no se pudo cargar el fotograma de correr: %s", frameName.c_str());
            continue;
        }
        runFrames.pushBack(frame);
    }

    // Crear la animación de correr
    if (!runFrames.empty()) {
        auto animation = Animation::createWithSpriteFrames(runFrames, 0.1f);
        runAnimation = Animate::create(animation);
        runAnimation->retain();
    }

    // Cargar los fotogramas de animación para estar inactivo
    for (int i = 1; i <= 6; ++i) {
        std::string frameName = "Warrior_Idle_" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64));
        if (frame == nullptr) {
            log("Error: no se pudo cargar el fotograma de estar inactivo: %s", frameName.c_str());
            continue;
        }
        idleFrames.pushBack(frame);
    }

    // Crear la animación de estar inactivo
    if (!idleFrames.empty()) {
        auto idleAnimationObj = Animation::createWithSpriteFrames(idleFrames, 0.2f);
        idleAnimation = Animate::create(idleAnimationObj);
        idleAnimation->retain();
    }

    // Cargar los fotogramas de animación para atacar
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 12; ++i) {
        std::string frameName = "Warrior_Attack_" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64));
        if (frame != nullptr) {
            attackFrames.pushBack(frame);
        }
        else {
            log("Error: no se pudo cargar el fotograma de ataque: %s", frameName.c_str());
        }
    }

    // Crear la animación de atacar
    if (!attackFrames.empty()) {
        auto attackAnimationObj = Animation::createWithSpriteFrames(attackFrames, 0.05f); // Ajusta la velocidad de la animación si es necesario
        attackAnimation = Animate::create(attackAnimationObj);
        attackAnimation->retain();
    }

    // Crear el sprite del jugador con el primer fotograma de "Idle" si existe
    if (!idleFrames.empty()) {
        player = Sprite::createWithSpriteFrame(idleFrames.front());
    }
    else if (!runFrames.empty()) {
        player = Sprite::createWithSpriteFrame(runFrames.front());
    }
    else {
        log("Error: no se pudieron cargar los fotogramas para el jugador.");
        return;
    }

    // Posicionar el personaje en el centro de la escena
    player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    player->setScale(1.5f); // Escalar del perosnaje *******************************************************************************************************
    this->addChild(player, 1);
    // voltear
    facingRight = true;

    // Crea un nodo fijo que no se moverá con la cámara
    auto fixedNode = Node::create();
    fixedNode->setPosition(Vec2::ZERO);
    this->addChild(fixedNode, 30);  // Añade el nodo fijo a la escena con un alto z-order


    PlayerData* playerData = PlayerData::getInstance();
    playerData->setPlayerName("Pam");
    playerData->setPlayerLevel(1);
    playerData->setPlayerAttack(20);
    playerData->setPlayerHealth(100);
}



// ---------------------------------------------------- M E T O D O     A T A C A R -------------------------------------------------------------------------------
void City::playAttackAnimation() {
    if (!player) return;  // Comprobar si el sprite del jugador existe

    // Detener cualquier otra animación que pueda estar en ejecución
    isAttacking = true;  // Indica que el personaje está atacando
    player->stopAllActions();

    // Reproducir sonido de ataque
    cocos2d::AudioEngine::play2d("AudioAtaque.mp3", false);  // 'false' significa que no se repetirá

    // Crear y configurar la animación de ataque
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 12; ++i) {
        std::string frameName = "Warrior_Attack_" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 75, 75));
        if (frame != nullptr) {
            attackFrames.pushBack(frame);
        }
    }

    if (!attackFrames.empty()) {
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.05f); // Ajustar la duración de cada frame si es necesario
        auto animateAttack = Animate::create(attackAnimation);

        // Configurar un callback para cuando la animación termine
        auto callback = CallFunc::create([this]() {
            isAttacking = false;  // Restablecer cuando la animación de ataque termine
            if (!keys[EventKeyboard::KeyCode::KEY_W] && !keys[EventKeyboard::KeyCode::KEY_S] &&
                !keys[EventKeyboard::KeyCode::KEY_A] && !keys[EventKeyboard::KeyCode::KEY_D]) {
                player->runAction(RepeatForever::create(idleAnimation));
            }
            else {
                auto runAction = RepeatForever::create(runAnimation);
                runAction->setTag(1);
                player->runAction(runAction);
            }
            });

        // Ejecutar la animación de ataque seguida del callback
        auto sequence = Sequence::create(animateAttack, callback, nullptr);
        player->runAction(sequence);
    }
}

//-------------------------------------------------------------------- M O V  U P D A T E ------------------------------------------------------------------
void City::update(float delta) {
    // Si el personaje está atacando, no se debe permitir otras animaciones 
    if (isAttacking) return;

    Vec2 movement(0, 0);
    bool isMoving = false;

    auto sceneSize = Vec2(Director::getInstance()->getVisibleSize().width * 2,
        Director::getInstance()->getVisibleSize().height * 2);

    auto checkCollision = [&](const Vec2& position) -> bool {
        int x = position.x / tileSize;
        int y = position.y / tileSize;
        if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
            return grid[x][y]->getTag() == 1;
        }
        return false;
        };

    auto checkEvent = [&](const Vec2& position) {
        int x = position.x / tileSize;
        int y = position.y / tileSize;
        if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
            int tag = grid[x][y]->getTag();
            if (tag == 3) {
                // Detener la música actual
                cocos2d::AudioEngine::stop(backgroundMusicId);
                // Cambiar a la escena de Interiores
                auto interiorScene = Interiores::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(0.9, interiorScene));
            }
            else if (tag == 4) {
                // Detener la música actual
                cocos2d::AudioEngine::stop(backgroundMusicId);
                // Cambiar a la escena de Dungeons
                auto dungeonScene = DFloor01::createScene(); 
                Director::getInstance()->replaceScene(TransitionFade::create(0.9, dungeonScene));
            }
        }
        };

    // Movimientos básicos con comprobación de colisiones y eventos
    if (keys[EventKeyboard::KeyCode::KEY_W] && player->getPosition().y < sceneSize.y - player->getContentSize().height / 2) {
        Vec2 newPos = player->getPosition() + Vec2(0, 400 * delta);
        if (!checkCollision(newPos)) {
            movement.y += 400 * delta;
            isMoving = true;
            checkEvent(newPos);
        }
    }
    if (keys[EventKeyboard::KeyCode::KEY_S] && player->getPosition().y > player->getContentSize().height / 2) {
        Vec2 newPos = player->getPosition() - Vec2(0, 400 * delta);
        if (!checkCollision(newPos)) {
            movement.y -= 400 * delta;
            isMoving = true;
            checkEvent(newPos);
        }
    }
    if (keys[EventKeyboard::KeyCode::KEY_A] && player->getPosition().x > player->getContentSize().width / 2) {
        Vec2 newPos = player->getPosition() - Vec2(400 * delta, 0);
        if (!checkCollision(newPos)) {
            movement.x -= 400 * delta;
            isMoving = true;
            if (facingRight) {
                facingRight = false;
                player->setFlippedX(true);
            }
            checkEvent(newPos);
        }
    }
    if (keys[EventKeyboard::KeyCode::KEY_D] && player->getPosition().x < sceneSize.x - player->getContentSize().width / 2) {
        Vec2 newPos = player->getPosition() + Vec2(400 * delta, 0);
        if (!checkCollision(newPos)) {
            movement.x += 400 * delta;
            isMoving = true;
            if (!facingRight) {
                facingRight = true;
                player->setFlippedX(false);
            }
            checkEvent(newPos);
        }
    }

    if (isMoving) {
        Vec2 newPosition = player->getPosition() + movement; 
        newPosition.x = std::max(newPosition.x, player->getContentSize().width / 2); 
        newPosition.x = std::min(newPosition.x, sceneSize.x - player->getContentSize().width / 2); 
        newPosition.y = std::max(newPosition.y, player->getContentSize().height / 2); 
        newPosition.y = std::min(newPosition.y, sceneSize.y - player->getContentSize().height / 2); 

        player->setPosition(newPosition);

        if (player->getActionByTag(2)) {
            player->stopActionByTag(2); // Detener la animación estática si está activa
        }
        if (!player->getActionByTag(1)) {
            auto runAction = RepeatForever::create(runAnimation);
            runAction->setTag(1);
            player->runAction(runAction);
        }
    }
    else {
        if (!player->getActionByTag(2)) {
            player->stopAllActions(); // Detener cualquier acción previa
            auto idleAction = RepeatForever::create(idleAnimation);
            idleAction->setTag(2);
            player->runAction(idleAction);
        }
    }

    //----------------------------------------------------- C A M R A ----------------------------------------------------------------------------------------------

     //Actualizar la posición de la cámara para seguir al jugador
    auto camera = this->getDefaultCamera();
    camera->setPosition(player->getPosition());
    camera->setScale(0.65f); // Un valor de escala menor agranda el zoom. 0.5 resulta en un zoom de 2x.

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------

}
