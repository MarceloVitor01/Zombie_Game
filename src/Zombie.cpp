#include "Zombie.h"
#include "Sprite.h"
#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"
#include "Bullet.h"
#include "Character.h"

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject &associated) : Component(associated)
{
    hp = 50;
    isDead = false;
    zombieCount++;

    Animator *animator = new Animator(associated);
    animator->AddAnimation("walking_right", Animation(0, 3, 0.15f, SDL_FLIP_NONE));
    animator->AddAnimation("walking_left", Animation(0, 3, 0.15f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead_right", Animation(5, 5, 0.1f, SDL_FLIP_NONE));
    animator->AddAnimation("dead_left", Animation(5, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(animator);
    animator->SetAnimation("walking_right");
}

Zombie::~Zombie()
{
    zombieCount--;
}

void Zombie::Start()
{
    Collider *collider = new Collider(associated, Vec2(0.7f, 0.9f));
    associated.AddComponent(collider);
}

void Zombie::Update(float dt)
{
    Animator *animator = associated.GetComponent<Animator>();

    if (hp <= 0 && !isDead)
    {
        isDead = true;
        Collider *col = associated.GetComponent<Collider>();
        if (col)
            associated.RemoveComponent(col);
        if (animator)
            animator->SetAnimation("dead_right");
    }

    if (isDead)
    {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 2.0f)
            associated.RequestDelete();
        return;
    }

    if (Character::player)
    {
        Vec2 myCenter = associated.box.Center();
        Vec2 playerCenter = Character::player->GetPlayerCenter();
        Vec2 dir = (playerCenter - myCenter).Normalize();

        associated.box.x += dir.x * 100.0f * dt;
        associated.box.y += dir.y * 100.0f * dt;

        if (animator)
        {
            if (dir.x > 0)
                animator->SetAnimation("walking_right");
            else
                animator->SetAnimation("walking_left");
        }
    }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type) { return type == "Zombie"; }

void Zombie::NotifyCollision(GameObject &other)
{
    Bullet *bullet = other.GetComponent<Bullet>();
    if (bullet && !bullet->targetsPlayer && !isDead)
    {
        hp -= bullet->GetDamage();
    }
}