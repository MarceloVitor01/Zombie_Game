#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "Music.h"
#include "GameObject.h"

class State
{
public:
    State();
    ~State();

    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();

private:
    void AddObject(int mouseX, int mouseY);
    void AddObject(GameObject *go);

    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif