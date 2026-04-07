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
        std::cout << "Erro: Tentativa de instanciar o Game mais de uma vez!" << std::endl;
        exit(EXIT_FAILURE);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(imageFlags) == 0)
    {
        std::cout << "Erro ao inicializar SDL_Image: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    int mixFlags = MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3;
    if (Mix_Init(mixFlags) == 0)
    {
        std::cout << "Erro ao inicializar SDL_Mixer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        std::cout << "Erro em Mix_OpenAudio: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Aloca 32 canais de áudio
    Mix_AllocateChannels(32);

    // 4. Cria a janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr)
    {
        std::cout << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 5. Cria o renderizador (Acelerado por Hardware)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 6. Instancia o estado inicial
    state = new State();
}

// ---------------------------------------------------------
// Destrutor
// ---------------------------------------------------------
Game::~Game()
{
    // Destrói na ordem inversa da inicialização
    delete state;

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------
State &Game::GetState()
{
    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

// ---------------------------------------------------------
// Game Loop Principal
// ---------------------------------------------------------
void Game::Run()
{
    // Roda enquanto o estado não requisitar a saída
    while (!state->QuitRequested())
    {
        // Atualiza a lógica do estado (por enquanto passando 0)
        state->Update(0.0f);

        // Renderiza o estado na tela
        state->Render();

        // Atualiza a tela com o que foi renderizado
        SDL_RenderPresent(renderer);

        // Limita o framerate para ~30 FPS
        SDL_Delay(33);
    }
}