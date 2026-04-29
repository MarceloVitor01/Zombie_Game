#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"

class Zombie : public Component
{
public:
    Zombie(GameObject &associated);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    int hp;
    Sound deathSound;
    float timeDead;
};

#endif