#ifndef NPC_H
#define NPC_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class NPC : public Component
{
public:
    NPC(GameObject &associated);
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject &other) override;

    int hp;

private:
    Timer moveTimer;
    Timer deathTimer;
    Vec2 target;
    bool isDead;
};

#endif