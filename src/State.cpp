#include "State.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "Character.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "Camera.h"

State::State() : music("Recursos/audio/BGM.wav")
{
    quitRequested = false;
    started = false;

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

    music.Play();
}

State::~State()
{
    objectArray.clear();
}

void State::Start()
{
    LoadAssets();
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

void State::LoadAssets() {}

void State::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }

    Camera::Update(dt);

    if (input.KeyPress(SDLK_SPACE))
    {
        int spawnX = input.GetMouseX() + Camera::pos.x;
        int spawnY = input.GetMouseY() + Camera::pos.y;
        AddObject(spawnX, spawnY);
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
    Sprite *sprite = new Sprite(*go, "Recursos/img/Enemy.png", 3, 2);
    go->AddComponent(sprite);

    Zombie *zombie = new Zombie(*go);
    go->AddComponent(zombie);

    go->box.x = mouseX - go->box.w / 2.0f;
    go->box.y = mouseY - go->box.h / 2.0f;

    AddObject(go);
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    std::shared_ptr<GameObject> sharedGo(go);
    objectArray.push_back(sharedGo);
    if (started)
    {
        sharedGo->Start();
    }
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i].get() == go)
        {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}