#include "Character.h"
#include "Sprite.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"

Character *Character::player = nullptr;

Character::Character(GameObject &associated, std::string sprite) : Component(associated)
{
    player = this;
    hp = 100;
    linearSpeed = 200.0f;
    facingRight = true;

    Sprite *sp = new Sprite(associated, sprite, 3, 4);
    associated.AddComponent(sp);

    Animator *anim = new Animator(associated);
    anim->AddAnimation("idle_right", Animation(0, 0, 0.1f, SDL_FLIP_NONE));
    anim->AddAnimation("idle_left", Animation(0, 0, 0.1f, SDL_FLIP_HORIZONTAL));
    anim->AddAnimation("walking_right", Animation(0, 3, 0.1f, SDL_FLIP_NONE));
    anim->AddAnimation("walking_left", Animation(0, 3, 0.1f, SDL_FLIP_HORIZONTAL));
    anim->AddAnimation("dead_right", Animation(0, 0, 0.1f, SDL_FLIP_NONE));
    anim->AddAnimation("dead_left", Animation(0, 0, 0.1f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(anim);

    anim->SetAnimation("idle_right");
}

Character::~Character()
{
    if (player == this)
    {
        player = nullptr;
    }
}

void Character::Start()
{
    GameObject *gunGo = new GameObject();
    Gun *gunComp = new Gun(*gunGo, Game::GetInstance().GetState().GetObjectPtr(&associated));
    gunGo->AddComponent(gunComp);
    gun = Game::GetInstance().GetState().AddObject(gunGo);
}

void Character::Update(float dt)
{
    Animator *animator = associated.GetComponent<Animator>();

    if (hp <= 0)
    {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 2.0f)
        {
            associated.RequestDelete();
        }
        return;
    }

    bool moved = false;

    while (!taskQueue.empty())
    {
        Command cmd = taskQueue.front();
        taskQueue.pop();

        if (cmd.type == MOVE)
        {
            if (cmd.pos.GetMagnitude() > 0)
            {
                speed = cmd.pos.Normalize() * linearSpeed;
                associated.box.x += speed.x * dt;
                associated.box.y += speed.y * dt;
                moved = true;

                if (speed.x > 0)
                    facingRight = true;
                else if (speed.x < 0)
                    facingRight = false;
            }
        }
        else if (cmd.type == SHOOT)
        {
            std::shared_ptr<GameObject> gunPtr = gun.lock();
            if (gunPtr)
            {
                Gun *g = gunPtr->GetComponent<Gun>();
                if (g)
                    g->Shoot(cmd.pos);
            }
        }
    }

    if (animator)
    {
        if (hp <= 0)
        {
            animator->SetAnimation(facingRight ? "dead_right" : "dead_left");
        }
        else if (moved)
        {
            animator->SetAnimation(facingRight ? "walking_right" : "walking_left");
        }
        else
        {
            animator->SetAnimation(facingRight ? "idle_right" : "idle_left");
        }
    }
}

void Character::Render() {}

bool Character::Is(std::string type)
{
    return type == "Character";
}

void Character::Issue(Command task)
{
    taskQueue.push(task);
}