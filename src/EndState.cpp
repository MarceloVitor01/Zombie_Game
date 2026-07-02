#include "EndState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

EndState::EndState(StateData stateData)
{
    this->stateData = stateData;
}

EndState::~EndState()
{
    objectArray.clear();
}

void EndState::LoadAssets()
{
    GameObject *bg = new GameObject();

    if (stateData.playerVictory)
    {
        bg->AddComponent(new Sprite(*bg, "Recursos/img/Win.png"));
        backgroundMusic.Open("Recursos/audio/endStateWin.ogg");
    }
    else
    {
        bg->AddComponent(new Sprite(*bg, "Recursos/img/Lose.png"));
        backgroundMusic.Open("Recursos/audio/endStateLose.ogg");
    }

    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);
}

void EndState::Start()
{
    LoadAssets();
    Camera::pos = Vec2(0, 0);
    StartArray();
    backgroundMusic.Play();
}

void EndState::Pause() {}

void EndState::Resume() {}

void EndState::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.QuitRequested())
        quitRequested = true;

    if (input.KeyPress(ESCAPE_KEY) || input.KeyPress(SDLK_SPACE))
    {
        popRequested = true;
    }

    UpdateArray(dt);
}

void EndState::Render()
{
    RenderArray();
}