#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Timer.h"

class Zombie : public Component
{
public:
    Zombie(GameObject &associated);
    ~Zombie();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject &other) override;

    static int zombieCount;

private:
    int hp;
    Timer deathTimer;
    bool isDead;
};

#endif