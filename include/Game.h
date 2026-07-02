#ifndef GAME_H
#define GAME_H

#include "SDL_include.h"
#include "State.h"
#include <string>
#include <stack>
#include <memory>

class Game
{
public:
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();
    float GetDeltaTime();
    void Push(State *state);

private:
    Game(std::string title, int width, int height);
    void CalculateDeltaTime();

    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;

    State *storedState;
    std::stack<std::unique_ptr<State>> stateStack;

    int frameStart;
    float dt;
};

#endif