#include "State.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "SDL_include.h"

State::State() : music("Recursos/audio/BGM.wav")
{
    quitRequested = false;

    GameObject *bgObj = new GameObject();
    SpriteRenderer *bgSprite = new SpriteRenderer(*bgObj, "Recursos/img/Background.png");
    bgObj->AddComponent(bgSprite);
    bgObj->box.x = 0;
    bgObj->box.y = 0;
    objectArray.emplace_back(bgObj);

    GameObject *mapObj = new GameObject();
    TileSet *tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap *tileMap = new TileMap(*mapObj, "Recursos/map/map.txt", tileSet);
    mapObj->AddComponent(tileMap);
    mapObj->box.x = 0;
    mapObj->box.y = 0;
    objectArray.emplace_back(mapObj);

    music.Play();
}

State::~State()
{
    objectArray.clear();
}

void State::LoadAssets() {}

void State::Update(float dt)
{
    SDL_Event event;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            AddObject(mouseX, mouseY);
        }
    }

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render()
{
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
    GameObject *go = new GameObject();

    SpriteRenderer *sprite = new SpriteRenderer(*go, "Recursos/img/Enemy.png", 3, 2);
    go->AddComponent(sprite);

    Zombie *zombie = new Zombie(*go);
    go->AddComponent(zombie);

    go->box.x = mouseX - go->box.w / 2.0f;
    go->box.y = mouseY - go->box.h / 2.0f;

    objectArray.emplace_back(go);
}