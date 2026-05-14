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

    void Start();
    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();

    std::weak_ptr<GameObject> AddObject(GameObject *go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);

private:
    void AddObject(int mouseX, int mouseY);

    Music music;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif