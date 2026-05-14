#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"

class PlayerController : public Component
{
public:
    PlayerController(GameObject &associated);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};

#endif