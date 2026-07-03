#include "EndState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Text.h"
#include "TitleState.h"

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

    // Texto de instrução para o EndState
    GameObject *textGo = new GameObject();
    std::string instrText = "ESC para sair | ESPACO para jogar novamente";
    Text *textStr = new Text(*textGo, "Recursos/font/neodgm.ttf", 36, Text::BLENDED, instrText, {200, 50, 50, 255});
    textGo->AddComponent(textStr);
    textGo->box.x = 1200 / 2 - textGo->box.w / 2;
    textGo->box.y = 820;
    AddObject(textGo);
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

    if (input.KeyPress(ESCAPE_KEY))
    {
        popRequested = true;
        quitRequested = true; // Força encerramento
    }

    // De acordo com a especificação, se apertar espaço, o jogo empilha um TitleState
    if (input.KeyPress(SDLK_SPACE))
    {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }

    UpdateArray(dt);
}

void EndState::Render()
{
    RenderArray();
}