#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "Animation.h"
#include <unordered_map>
#include <string>

class Animator : public Component
{
public:
    Animator(GameObject &associated);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetAnimation(std::string name);
    void AddAnimation(std::string name, Animation anim);

private:
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation;
    int currentFrame;
    float timeElapsed;
};

#endif