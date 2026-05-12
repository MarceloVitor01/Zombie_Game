#include "Animator.h"
#include "Sprite.h"
#include "GameObject.h"

Animator::Animator(GameObject &associated) : Component(associated)
{
    currentFrame = 0;
    timeElapsed = 0;
}

void Animator::Update(float dt)
{
    if (currentAnimation == "")
        return;

    Animation &anim = animations[currentAnimation];

    if (anim.frameTime > 0)
    {
        timeElapsed += dt;
        if (timeElapsed >= anim.frameTime)
        {
            currentFrame++;
            if (currentFrame > anim.frameEnd)
            {
                currentFrame = anim.frameStart;
            }
            timeElapsed -= anim.frameTime;

            Sprite *sr = associated.GetComponent<Sprite>();
            if (sr != nullptr)
            {
                sr->SetFrame(currentFrame);
            }
        }
    }
}

void Animator::Render() {}

bool Animator::Is(std::string type)
{
    return type == "Animator";
}

void Animator::SetAnimation(std::string name)
{
    if (animations.find(name) != animations.end())
    {
        currentAnimation = name;
        Animation &anim = animations[name];
        currentFrame = anim.frameStart;
        timeElapsed = 0;

        Sprite *sr = associated.GetComponent<Sprite>();
        if (sr != nullptr)
        {
            sr->SetFrame(currentFrame);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim)
{
    if (animations.find(name) == animations.end())
    {
        animations[name] = anim;
    }
}