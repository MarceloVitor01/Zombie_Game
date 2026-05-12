#include "Zombie.h"
#include "GameObject.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie(GameObject &associated) : Component(associated), deathSound("Recursos/audio/Dead.wav"), hitSound("Recursos/audio/Hit1.wav")
{
    hp = 30;
    isDead = false;
    hit = false;

    Animator *animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.1f));
    animator->AddAnimation("hit", Animation(4, 4, 0.2f));
    animator->AddAnimation("dead", Animation(5, 5, 0.1f));
    associated.AddComponent(animator);

    animator->SetAnimation("walking");
}

void Zombie::Update(float dt)
{
    Animator *animator = associated.GetComponent<Animator>();

    if (isDead)
    {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 5.0f)
        {
            associated.RequestDelete();
        }
        return;
    }

    if (hit)
    {
        hitTimer.Update(dt);
        if (hitTimer.Get() >= 0.5f)
        {
            hit = false;
            if (animator != nullptr)
            {
                animator->SetAnimation("walking");
            }
        }
    }

    InputManager &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        float mouseWorldX = input.GetMouseX() + Camera::pos.x;
        float mouseWorldY = input.GetMouseY() + Camera::pos.y;

        if (associated.box.Contains(mouseWorldX, mouseWorldY))
        {
            hp -= 10;
            hitSound.Play(1);

            if (hp <= 0)
            {
                isDead = true;
                deathSound.Play(1);
                Animator *animator = associated.GetComponent<Animator>();
                if (animator != nullptr)
                {
                    animator->SetAnimation("dead");
                }
            }
            else
            {
                hit = true;
                hitTimer.Restart();
                if (animator != nullptr)
                {
                    animator->SetAnimation("hit");
                }
            }
        }
    }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type)
{
    return type == "Zombie";
}