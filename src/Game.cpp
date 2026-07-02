#include "Game.h"
#include "Resources.h"
#include "InputManager.h"
#include <stdexcept>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height)
{
    if (instance != nullptr)
        throw std::logic_error("A instância de Game já existe!");
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
        throw std::runtime_error(SDL_GetError());
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
        throw std::runtime_error(SDL_GetError());
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) == 0)
        throw std::runtime_error(SDL_GetError());
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        throw std::runtime_error(SDL_GetError());
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr)
        throw std::runtime_error(SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
        throw std::runtime_error(SDL_GetError());

    storedState = nullptr;
    dt = 0;
    frameStart = SDL_GetTicks();
}

Game::~Game()
{
    if (storedState != nullptr)
        delete storedState;
    while (!stateStack.empty())
        stateStack.pop();

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game &Game::GetInstance()
{
    if (instance == nullptr)
        instance = new Game("Marcelo Vitor - 221030034", 1200, 900);
    return *instance;
}

State &Game::GetState()
{
    return *stateStack.top();
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::Push(State *state)
{
    storedState = state;
}

void Game::Run()
{
    if (storedState != nullptr)
    {
        stateStack.push(std::unique_ptr<State>(storedState));
        storedState = nullptr;
        stateStack.top()->Start();
    }

    if (stateStack.empty())
        return;

    while (!stateStack.empty() && !stateStack.top()->QuitRequested())
    {
        if (stateStack.top()->PopRequested())
        {
            stateStack.pop();

            // ATENÇÃO: As 3 funções Resources::Clear foram removidas
            // daqui para evitar apagar telas que ainda serão usadas!

            if (!stateStack.empty())
            {
                stateStack.top()->Resume();
            }
        }

        if (storedState != nullptr)
        {
            if (!stateStack.empty())
            {
                stateStack.top()->Pause();
            }
            stateStack.push(std::unique_ptr<State>(storedState));
            storedState = nullptr;
            stateStack.top()->Start();
        }

        if (stateStack.empty())
            break;

        CalculateDeltaTime();
        InputManager::GetInstance().Update();

        stateStack.top()->Update(dt);
        stateStack.top()->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    while (!stateStack.empty())
        stateStack.pop();
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime()
{
    int frameEnd = SDL_GetTicks();
    dt = (frameEnd - frameStart) / 1000.0f;
    frameStart = frameEnd;
}

float Game::GetDeltaTime()
{
    return dt;
}