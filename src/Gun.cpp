#include "Gun.h"
#include "Sprite.h"
#include "Animator.h"
#include "Bullet.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include <cmath>

Gun::Gun(GameObject &associated, std::weak_ptr<GameObject> character)
    : Component(associated), character(character), shotSound("Recursos/audio/Range.wav"), reloadSound("Recursos/audio/PumpAction.mp3")
{
    cooldownState = 0;

    Sprite *sp = new Sprite(associated, "Recursos/img/Gun.png", 3, 2);
    associated.AddComponent(sp);

    Animator *anim = new Animator(associated);
    anim->AddAnimation("idle", Animation(0, 0, 1.0f));
    anim->AddAnimation("reloading", Animation(1, 5, 0.1f));
    associated.AddComponent(anim);

    anim->SetAnimation("idle");
}

void Gun::Update(float dt)
{
    std::shared_ptr<GameObject> charGo = character.lock();
    if (!charGo || charGo->IsDead())
    {
        associated.RequestDelete();
        return;
    }

    InputManager &input = InputManager::GetInstance();
    float mouseX = input.GetMouseX() + Camera::pos.x;
    float mouseY = input.GetMouseY() + Camera::pos.y;
    Vec2 mousePos(mouseX, mouseY);

    Vec2 charCenter = charGo->box.Center();
    float angle = charCenter.GetAngle(mousePos);
    associated.angleDeg = angle * 180.0f / M_PI;

    associated.box.SetCenter(charCenter);
    Vec2 offset(30, 0);
    offset = offset.GetRotated(angle);
    associated.box.x += offset.x;
    associated.box.y += offset.y;

    Sprite *sp = associated.GetComponent<Sprite>();
    if (sp)
    {
        if (associated.angleDeg > 90 || associated.angleDeg < -90)
            sp->SetFlip(SDL_FLIP_VERTICAL);
        else
            sp->SetFlip(SDL_FLIP_NONE);
    }

    if (cooldownState != 0)
    {
        cdTimer.Update(dt);
        Animator *anim = associated.GetComponent<Animator>();

        if (cooldownState == 1 && cdTimer.Get() > 0.3f)
        {
            cooldownState = 2;
            cdTimer.Restart();
            if (anim)
            {
                anim->SetAnimation("reloading");
            }
            reloadSound.Play(1);
        }
        else if (cooldownState == 2 && cdTimer.Get() > 0.4f)
        {
            cooldownState = 3;
            cdTimer.Restart();
            if (anim)
                anim->SetAnimation("idle");
        }
        else if (cooldownState == 3 && cdTimer.Get() > 0.3f)
        {
            cooldownState = 0;
            cdTimer.Restart();
        }
    }
}

void Gun::Render() {}

bool Gun::Is(std::string type) { return type == "Gun"; }

void Gun::Shoot(Vec2 target)
{
    if (cooldownState == 0)
    {
        Vec2 center = associated.box.Center();
        float angle = center.GetAngle(target);
        associated.angleDeg = angle * 180.0f / M_PI;

        shotSound.Play(1);
        cooldownState = 1;
        cdTimer.Restart();

        GameObject *bulletGo = new GameObject();
        Vec2 tip(associated.box.w / 2.0f, 0);
        tip = tip.GetRotated(angle);
        bulletGo->box.x = center.x + tip.x;
        bulletGo->box.y = center.y + tip.y;

        Bullet *bullet = new Bullet(*bulletGo, angle, 500.0f, 10, 1000.0f, false);
        bulletGo->AddComponent(bullet);
        Game::GetInstance().GetState().AddObject(bulletGo);
    }
}