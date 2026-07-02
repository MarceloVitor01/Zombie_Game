#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"

TitleState::TitleState()
{
    GameObject *bg = new GameObject();
    Sprite *sp = new Sprite(*bg, "Recursos/img/Title.png");
    bg->AddComponent(sp);
    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets() {}

void TitleState::Start()
{
    Camera::pos = Vec2(0, 0);
    StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume()
{
    Camera::pos = Vec2(0, 0);
}

void TitleState::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }

    if (input.KeyPress(SDLK_SPACE))
    {
        Game::GetInstance().Push(new StageState());
    }

    UpdateArray(dt);
}

void TitleState::Render()
{
    RenderArray();
}