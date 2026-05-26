#include "NPC.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Animator.h"
#include "Bullet.h"
#include "Zombie.h"
#include <cstdlib>

NPC::NPC(GameObject &associated) : Component(associated)
{
    hp = 30;
    isDead = false;

    Sprite *sp = new Sprite(associated, "Recursos/img/NPC.png", 3, 4);
    associated.AddComponent(sp);

    Animator *anim = new Animator(associated);
    anim->AddAnimation("idle", Animation(0, 0, 0.1f, SDL_FLIP_NONE));
    anim->AddAnimation("walk", Animation(0, 3, 0.15f, SDL_FLIP_NONE));
    anim->AddAnimation("dead", Animation(0, 0, 0.1f, SDL_FLIP_VERTICAL));
    associated.AddComponent(anim);
    anim->SetAnimation("idle");

    target = Vec2((rand() % 1000), (rand() % 1000));
}

void NPC::Start()
{
    Collider *col = new Collider(associated, Vec2(0.6f, 0.8f));
    associated.AddComponent(col);
}

void NPC::Update(float dt)
{
    Animator *anim = associated.GetComponent<Animator>();

    if (hp <= 0 && !isDead)
    {
        isDead = true;
        Collider *col = associated.GetComponent<Collider>();
        if (col)
            associated.RemoveComponent(col);
        if (anim)
            anim->SetAnimation("dead");
    }

    if (isDead)
    {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 2.0f)
            associated.RequestDelete();
        return;
    }

    moveTimer.Update(dt);
    if (moveTimer.Get() > 3.0f)
    {
        moveTimer.Restart();
        target = associated.box.Center() + Vec2((rand() % 400) - 200, (rand() % 400) - 200);
    }

    Vec2 center = associated.box.Center();
    if (center.Distance(target) > 5.0f)
    {
        Vec2 dir = (target - center).Normalize();
        associated.box.x += dir.x * 100.0f * dt;
        associated.box.y += dir.y * 100.0f * dt;

        if (anim)
            anim->SetAnimation("walk");
        Sprite *sp = associated.GetComponent<Sprite>();
        if (sp)
        {
            if (dir.x < 0)
                sp->SetFlip(SDL_FLIP_HORIZONTAL);
            else
                sp->SetFlip(SDL_FLIP_NONE);
        }
    }
    else
    {
        if (anim)
            anim->SetAnimation("idle");
    }
}

void NPC::Render() {}

bool NPC::Is(std::string type) { return type == "NPC"; }

void NPC::NotifyCollision(GameObject &other)
{
    if (isDead)
        return;

    Zombie *z = other.GetComponent<Zombie>();
    if (z)
        hp = 0;

    Bullet *b = other.GetComponent<Bullet>();
    if (b && !b->targetsPlayer)
        hp -= b->GetDamage();
}