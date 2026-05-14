#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"
#include "Command.h"
#include <memory>
#include <queue>
#include <string>

class Character : public Component
{
public:
    Character(GameObject &associated, std::string sprite);
    ~Character();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Issue(Command task);

    static Character *player;
    int hp;

private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    Timer deathTimer;
    bool facingRight;
};

#endif