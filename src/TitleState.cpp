#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"
#include "Text.h"

TitleState::TitleState() : showText(true)
{
    GameObject *bg = new GameObject();
    Sprite *sp = new Sprite(*bg, "Recursos/img/Title.png");
    bg->AddComponent(sp);
    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);

    GameObject *textGo = new GameObject();
    Text *textStr = new Text(*textGo, "Recursos/font/neodgm.ttf", 40, Text::BLENDED, "Pressione ESPACO para jogar", {255, 255, 255, 255});
    textGo->AddComponent(textStr);
    textGo->box.x = 1200 / 2 - textGo->box.w / 2;
    textGo->box.y = 750;
    textObj = AddObject(textGo);
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

    textTimer.Update(dt);
    if (textTimer.Get() > 0.6f)
    {
        showText = !showText;
        std::shared_ptr<GameObject> textPtr = textObj.lock();
        if (textPtr)
        {
            Text *textComp = textPtr->GetComponent<Text>();
            if (textComp)
            {
                if (showText)
                    textComp->SetColor({255, 255, 255, 255});
                else
                    textComp->SetColor({255, 255, 255, 0});
            }
        }
        textTimer.Restart();
    }

    UpdateArray(dt);
}

void TitleState::Render()
{
    RenderArray();
}