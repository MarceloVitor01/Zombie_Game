#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

class State
{
public:
    State();

    void LoadAssets();

    void Update(float dt);

    void Render();

    bool QuitRequested();

private:
    Sprite bg;

    Music music;

    bool quitRequested;
};

#endif