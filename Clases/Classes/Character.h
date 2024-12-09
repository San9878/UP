#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    virtual ~Character() {}  // Destructor virtual para una base apropiada

    // Métodos virtuales puros que deben ser implementados por las clases derivadas
    virtual int getAttackPower() const = 0;
    virtual int getDefense() const = 0;
    virtual int getHealth() const = 0;
    virtual void setHealth(int health) = 0;
};

#endif // CHARACTER_H
