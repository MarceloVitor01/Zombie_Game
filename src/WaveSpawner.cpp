#include "WaveSpawner.h"
#include "GameObject.h"
#include "Game.h"
#include "State.h"
#include "Zombie.h"
#include "NPC.h"
#include "Sprite.h"
#include "Character.h"

WaveSpawner::WaveSpawner(GameObject &associated) : Component(associated)
{
    waiting = false;
    currentWaitTime = 0;
}

void WaveSpawner::AddCommand(WaveAction action, float timeToWait, Vec2 pos)
{
    WaveCommand cmd;
    cmd.action = action;
    cmd.timeToWait = timeToWait;
    cmd.pos = pos;
    commands.push(cmd);
}

void WaveSpawner::Update(float dt)
{
    if (commands.empty())
    {
        if (Zombie::zombieCount == 0 && Character::player != nullptr && Character::player->hp > 0)
        {
            Game::GetInstance().GetState().EndGame(true);
            associated.RequestDelete();
        }
        return;
    }

    if (waiting)
    {
        waitTimer.Update(dt);
        if (waitTimer.Get() >= currentWaitTime)
        {
            waiting = false;
            waitTimer.Restart();
            commands.pop();
        }
        return;
    }

    WaveCommand cmd = commands.front();

    if (cmd.action == WaveAction::WAIT)
    {
        waiting = true;
        currentWaitTime = cmd.timeToWait;
        return;
    }

    if (cmd.action == WaveAction::SPAWN_ZOMBIE)
    {
        GameObject *go = new GameObject();
        Sprite *sprite = new Sprite(*go, "Recursos/img/Enemy.png", 3, 2);
        go->AddComponent(sprite);
        Zombie *zombie = new Zombie(*go);
        go->AddComponent(zombie);
        go->box.x = cmd.pos.x - go->box.w / 2.0f;
        go->box.y = cmd.pos.y - go->box.h / 2.0f;
        Game::GetInstance().GetState().AddObject(go);
    }
    else if (cmd.action == WaveAction::SPAWN_NPC)
    {
        GameObject *go = new GameObject();
        NPC *npc = new NPC(*go);
        go->AddComponent(npc);
        go->box.x = cmd.pos.x - go->box.w / 2.0f;
        go->box.y = cmd.pos.y - go->box.h / 2.0f;
        Game::GetInstance().GetState().AddObject(go);
    }

    commands.pop();
}

void WaveSpawner::Render() {}

bool WaveSpawner::Is(std::string type) { return type == "WaveSpawner"; }