#include "Zombie.h"
#include "GameObject.h"
#include "Animator.h"

Zombie::Zombie(GameObject &associated) : Component(associated), deathSound("Recursos/audio/Dead.wav")
{
    hp = 100;

    Animator *animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    associated.AddComponent(animator);

    animator->SetAnimation("walking");
}

void Zombie::Update(float dt)
{
    if (hp > 0)
    {
        hp -= 1;
        if (hp <= 0)
        {
            Animator *animator = associated.GetComponent<Animator>();
            if (animator != nullptr)
            {
                animator->SetAnimation("dead");
            }

            deathSound.Play(1);
        }
    }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type)
{
    return type == "Zombie";
}