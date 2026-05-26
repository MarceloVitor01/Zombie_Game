#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"
#include <queue>

enum class WaveAction
{
    SPAWN_ZOMBIE,
    SPAWN_NPC,
    WAIT
};

struct WaveCommand
{
    WaveAction action;
    float timeToWait;
    Vec2 pos;
};

class WaveSpawner : public Component
{
public:
    WaveSpawner(GameObject &associated);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void AddCommand(WaveAction action, float timeToWait, Vec2 pos);

private:
    std::queue<WaveCommand> commands;
    Timer waitTimer;
    bool waiting;
    float currentWaitTime;
};

#endif