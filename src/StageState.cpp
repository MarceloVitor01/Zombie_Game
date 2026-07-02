#include "StageState.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "Character.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Collision.h"
#include "WaveSpawner.h"
#include "Game.h"
#include "EndState.h"
#include "StateData.h"
#include <algorithm>

StageState::StageState() : music("Recursos/audio/BGM.wav")
{
    GameObject *bgObj = new GameObject();
    Sprite *bgSprite = new Sprite(*bgObj, "Recursos/img/Background.png");
    bgSprite->SetCameraFollower(true);
    bgObj->AddComponent(bgSprite);
    bgObj->box.x = 0;
    bgObj->box.y = 0;
    AddObject(bgObj);

    GameObject *mapObj = new GameObject();
    TileSet *tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap *tileMap = new TileMap(*mapObj, "Recursos/map/map.txt", tileSet);
    mapObj->AddComponent(tileMap);
    mapObj->box.x = 0;
    mapObj->box.y = 0;
    AddObject(mapObj);

    GameObject *charGo = new GameObject();
    Character *character = new Character(*charGo, "Recursos/img/Player.png");
    charGo->AddComponent(character);

    PlayerController *pc = new PlayerController(*charGo);
    charGo->AddComponent(pc);

    charGo->box.x = 1280;
    charGo->box.y = 1280;
    AddObject(charGo);

    Camera::Follow(charGo);

    GameObject *waveGo = new GameObject();
    WaveSpawner *spawner = new WaveSpawner(*waveGo);
    spawner->AddCommand(WaveAction::WAIT, 2.0f, Vec2(0, 0));
    spawner->AddCommand(WaveAction::SPAWN_NPC, 0.0f, Vec2(1000, 1000));
    spawner->AddCommand(WaveAction::SPAWN_NPC, 0.0f, Vec2(1200, 1000));
    spawner->AddCommand(WaveAction::WAIT, 3.0f, Vec2(0, 0));
    spawner->AddCommand(WaveAction::SPAWN_ZOMBIE, 0.0f, Vec2(800, 1200));
    spawner->AddCommand(WaveAction::SPAWN_ZOMBIE, 0.0f, Vec2(1500, 1200));
    spawner->AddCommand(WaveAction::WAIT, 5.0f, Vec2(0, 0));
    spawner->AddCommand(WaveAction::SPAWN_ZOMBIE, 0.0f, Vec2(1300, 1500));
    spawner->AddCommand(WaveAction::SPAWN_ZOMBIE, 0.0f, Vec2(1400, 1500));
    spawner->AddCommand(WaveAction::SPAWN_ZOMBIE, 0.0f, Vec2(1500, 1500));
    waveGo->AddComponent(spawner);
    AddObject(waveGo);
}

StageState::~StageState()
{
    objectArray.clear();
}

void StageState::LoadAssets() {}

void StageState::Start()
{
    LoadAssets();
    StartArray();
    music.Play();
}

void StageState::Pause() {}

void StageState::Resume() {}

void StageState::Update(float dt)
{
    Camera::Update(dt);
    InputManager &input = InputManager::GetInstance();

    if (input.QuitRequested())
        quitRequested = true;
    if (input.KeyPress(ESCAPE_KEY))
        popRequested = true;

    UpdateArray(dt);

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        for (size_t j = i + 1; j < objectArray.size(); j++)
        {
            Collider *colA = objectArray[i]->GetComponent<Collider>();
            Collider *colB = objectArray[j]->GetComponent<Collider>();
            if (colA && colB)
            {
                if (Collision::IsColliding(colA->box, colB->box, objectArray[i]->angleDeg * M_PI / 180.0f, objectArray[j]->angleDeg * M_PI / 180.0f))
                {
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }
        }
    }

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

    if (Character::player == nullptr)
    {
        popRequested = true;
        StateData data;
        data.playerVictory = false;
        Game::GetInstance().Push(new EndState(data));
    }
    else
    {
        bool spawnerAlive = false;
        for (size_t i = 0; i < objectArray.size(); i++)
        {
            if (objectArray[i]->GetComponent<WaveSpawner>() != nullptr)
            {
                spawnerAlive = true;
                break;
            }
        }
        if (!spawnerAlive)
        {
            popRequested = true;
            StateData data;
            data.playerVictory = true;
            Game::GetInstance().Push(new EndState(data));
        }
    }
}

void StageState::Render()
{
    if (objectArray.size() > 0)
        objectArray[0]->Render();
    if (objectArray.size() > 1)
        objectArray[1]->Render();

    std::vector<GameObject *> entities;
    for (size_t i = 2; i < objectArray.size(); i++)
    {
        entities.push_back(objectArray[i].get());
    }

    std::sort(entities.begin(), entities.end(), [](GameObject *a, GameObject *b)
              { return (a->box.y + a->box.h) < (b->box.y + b->box.h); });

    for (size_t i = 0; i < entities.size(); i++)
    {
        entities[i]->Render();
    }
}