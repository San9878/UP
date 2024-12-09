#include "Enemy.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

Enemy* Enemy::createEnemy(const Vec2& position) {
    auto enemy = new Enemy();
    if (enemy && enemy->initWithFile("EN01idle01.png")) {
        enemy->setPosition(position);
        enemy->initOptions();
        enemy->initAnimations();
        enemy->idle();
        enemy->autorelease();
        enemy->scheduleUpdate();
  
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

void Enemy::initOptions() {
    this->level = 1;
    this->attackPower = 5;
    this->health = 40;
    
}

void Enemy::initAnimations() {
    loadIdleAnimation();
    loadWalkAnimation();
    loadAttackAnimation();
    idle();  // Comienza con la animación idle
}


//--------------------------------------------------------------I D L E--------------------------------------------------------------------------
void Enemy::loadIdleAnimation() {
    Vector<SpriteFrame*> frames;
    // Cargar los fotogramas de animación para estar inactivo (Idle)
    for (int i = 1; i <= 7; ++i) {
        std::string frameName = "EN01idle0" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 80));
        if (frame) {
            frames.pushBack(frame);
        }
        else {
            log("Error: no se pudo cargar el fotograma de estar inactivo: %s", frameName.c_str());
        }
    }
    idleAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
    idleAnimation->retain();
}

void Enemy::idle() {
    if (currentAction == "idle") return;
    checkFlip(); // Asegúrate de que la orientación es correcta antes de estar inactivo
    currentAction = "idle";
    this->stopAllActions();
    auto animate = Animate::create(idleAnimation);
    auto repeat = RepeatForever::create(animate);
    this->runAction(repeat);
}


//--------------------------------------------- W A L K-----------------------------------------------------------------------

void Enemy::loadWalkAnimation() {
    Vector<SpriteFrame*> frames;
    // Cargar los fotogramas de animación para caminar
    for (int i = 1; i <= 6; ++i) {
        std::string frameName = "EN01walk0" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 80, 80));
        if (frame) {
            frames.pushBack(frame);
        }
        else {
            log("Error: no se pudo cargar el fotograma de caminar: %s", frameName.c_str());
        }
    }
    walkAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
    walkAnimation->retain();
}

void Enemy::walk() {
    if (currentAction == "walk") return;
    checkFlip(); // Asegúrate de que la orientación es correcta antes de caminar
    currentAction = "walk";
    this->stopAllActions();
    auto animate = Animate::create(walkAnimation);
    auto repeat = RepeatForever::create(animate);
    this->runAction(repeat);
}

//--------------------------------------------------------------ATACK--------------------------------------------------------------------------
void Enemy::loadAttackAnimation() {

    // Reproducir sonido de ataque
    cocos2d::AudioEngine::play2d("AudioAtaque.mp3", false);  // 'false' significa que no se repetirá

    Vector<SpriteFrame*> frames;
    // Cargar los fotogramas de animación para atacar
    for (int i = 1; i <= 7; ++i) {
        std::string frameName = "EN01attack0" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 80, 80));
        if (frame) {
            frames.pushBack(frame);
        }
        else {
            log("Error: no se pudo cargar el fotograma de atacar: %s", frameName.c_str());
        }
    }
    attackAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
    attackAnimation->retain();
}

void Enemy::attack() {
    // Reproducir sonido de ataque
    cocos2d::AudioEngine::play2d("AudioAtaque.mp3", false);  // 'false' significa que no se repetirá 
    if (currentAction == "attack") return;
    checkFlip(); // Asegúrate de que la orientación es correcta antes de atacar
    currentAction = "attack";
    this->stopAllActions();
    auto animate = Animate::create(attackAnimation);
    auto repeat = RepeatForever::create(animate);
    this->runAction(repeat);
}
//---------------------------------------------- H I T -----------------------------------------------------------------------------------
void Enemy::hit() {
    // Cargar los fotogramas de animación para recibir daño
    for (int i = 1; i <= 3; ++i) {
        std::string frameName = "EN01hit0" + std::to_string(i) + ".png";
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 100));
        if (frame == nullptr) {
            log("Error: no se pudo cargar el fotograma de recibir daño: %s", frameName.c_str());
        }
        else {
            hitFrames.pushBack(frame);
        }
    }
}

//--------------------------------------------- UPDATE ----------------------------------------------------------------------------------------------

void Enemy::update(float delta) {
    if (isPlayerNear()) {
        if (currentAction != "attack") {
            this->stopAllActions(); // Detiene cualquier animación actual
            attack(); // Inicia la animación de ataque
        }
    }
    else {
        if (currentAction != "idle") {
            this->stopAllActions(); // Detiene cualquier animación actual
            idle(); // Inicia la animación de estar inactivo
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

bool Enemy::isPlayerNear() {
    float distance = this->getPosition().distance(player->getPosition());
    return distance <= 100;
}

void Enemy::setPlayerReference(Node* player) {
    this->player = player;
}

void Enemy::checkFlip() {
    if (player != nullptr) {
        // Voltea el sprite si el jugador está a la izquierda, no a la derecha
        bool shouldFlip = getPosition().x > player->getPosition().x;
        setFlippedX(shouldFlip); // Voltea el sprite dependiendo de la posición del jugador
    }
    else {
        log("Error: Player reference is null in checkFlip.");
    }
}


