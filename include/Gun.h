#ifndef GUN_H
#define GUN_H

#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"
#include <memory>

class Gun : public Component
{
public:
    Gun(GameObject &associated, std::weak_ptr<GameObject> character);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Shoot(Vec2 target);

private:
    std::weak_ptr<GameObject> character;
    Sound shotSound;
    Sound reloadSound;
    int cooldownState;
    Timer cdTimer;
};

#endif