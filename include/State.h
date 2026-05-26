#ifndef STATE_H
#define STATE_H

#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>

class State
{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject *go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);

    void EndGame(bool win);

private:
    void AddObject(int mouseX, int mouseY);
    Music music;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;

    bool endGameFlag;
    bool winFlag;
};

#endif