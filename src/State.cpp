#include "State.h"
#include "SDL_include.h"

State::State() : bg("Recursos/img/Background.png"), music("Recursos/audio/BGM.wav")
{
    quitRequested = false;

    music.Play();
}

void State::LoadAssets() {}

void State::Update(float dt)
{
    if (SDL_QuitRequested())
    {
        quitRequested = true;
    }
}

void State::Render()
{
    bg.Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}