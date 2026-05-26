#include "Character.h"
#include "Sprite.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"
#include "Collider.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Camera.h"

Character *Character::player = nullptr;

Character::Character(GameObject &associated, std::string sprite)
    : Component(associated), hitSound("Recursos/audio/Hit1.wav"), deadSound("Recursos/audio/Dead.wav")
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
    anim->AddAnimation("dead_right", Animation(10, 11, 0.2f, SDL_FLIP_NONE));
    anim->AddAnimation("dead_left", Animation(10, 11, 0.2f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(anim);

    anim->SetAnimation("idle_right");
}

Character::~Character()
{
    if (player == this)
        player = nullptr;
}

void Character::Start()
{
    Collider *collider = new Collider(associated, Vec2(0.6f, 0.8f));
    associated.AddComponent(collider);

    GameObject *gunGo = new GameObject();
    Gun *gunComp = new Gun(*gunGo, Game::GetInstance().GetState().GetObjectPtr(&associated));
    gunGo->AddComponent(gunComp);
    gun = Game::GetInstance().GetState().AddObject(gunGo);
}

void Character::Update(float dt)
{
    Animator *animator = associated.GetComponent<Animator>();
    damageTimer.Update(dt);

    if (hp <= 0)
    {
        if (animator)
            animator->SetAnimation(facingRight ? "dead_right" : "dead_left");

        deathTimer.Update(dt);
        if (deathTimer.Get() >= 2.0f)
        {
            // AQUI ESTÁ: Se o jogador morrer, o ecrã muda para LOSE
            Game::GetInstance().GetState().EndGame(false);
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
        if (moved)
            animator->SetAnimation(facingRight ? "walking_right" : "walking_left");
        else
            animator->SetAnimation(facingRight ? "idle_right" : "idle_left");
    }
}

void Character::Render() {}

bool Character::Is(std::string type) { return type == "Character"; }

void Character::Issue(Command task) { taskQueue.push(task); }

Vec2 Character::GetPlayerCenter()
{
    return associated.box.Center();
}

void Character::NotifyCollision(GameObject &other)
{
    if (hp <= 0)
        return;

    Zombie *zombie = other.GetComponent<Zombie>();
    if (zombie && damageTimer.Get() > 1.0f)
    {
        hp -= 10;
        damageTimer.Restart();
        if (hp > 0)
            hitSound.Play(1);
        else
        {
            deadSound.Play(1);
            Camera::Unfollow();
        }
    }

    Bullet *bullet = other.GetComponent<Bullet>();
    if (bullet && bullet->targetsPlayer)
    {
        hp -= bullet->GetDamage();
        if (hp <= 0)
        {
            deadSound.Play(1);
            Camera::Unfollow();
        }
    }
}