#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Timer.h"
#include <memory>

class TitleState : public State
{
public:
    TitleState();
    ~TitleState();
    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;
    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Timer textTimer;
    bool showText;
    std::weak_ptr<GameObject> textObj;
};

#endif