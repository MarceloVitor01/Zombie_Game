#include "Game.h"
#include "State.h"
#include <iostream>

Game *Game::instance = nullptr;

Game &Game::GetInstance()
{
    if (instance != nullptr)
    {
        return *instance;
    }

    instance = new Game("Marcelo Vitor - 221030034", 1200, 900);
    return *instance;
}

Game::Game(std::string title, int width, int height)
{
    if (instance != nullptr)
    {
        exit(EXIT_FAILURE);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        exit(EXIT_FAILURE);
    }

    int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(imageFlags) == 0)
    {
        exit(EXIT_FAILURE);
    }

    int mixFlags = MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3;
    if (Mix_Init(mixFlags) == 0)
    {
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        exit(EXIT_FAILURE);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    frameStart = SDL_GetTicks();
    dt = 0;

    state = new State();
}

Game::~Game()
{
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

State &Game::GetState()
{
    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::CalculateDeltaTime()
{
    int currentTicks = SDL_GetTicks();
    dt = (currentTicks - frameStart) / 1000.0f;
    frameStart = currentTicks;
}

float Game::GetDeltaTime()
{
    return dt;
}

void Game::Run()
{
    while (!state->QuitRequested())
    {
        CalculateDeltaTime();

        state->Update(GetDeltaTime());
        state->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}