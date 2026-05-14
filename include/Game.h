#ifndef GAME_H
#define GAME_H

#include "SDL_include.h"
#include "State.h"
#include <string>

class Game
{
public:
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();
    float GetDeltaTime();

private:
    Game(std::string title, int width, int height);
    void CalculateDeltaTime();

    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
    int frameStart;
    float dt;
};

#endif