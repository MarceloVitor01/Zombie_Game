#include "Bullet.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Collider.h"
#include "Zombie.h"
#include "Character.h"
#include <cmath>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer)
    : Component(associated), targetsPlayer(targetsPlayer), distanceLeft(maxDistance), damage(damage)
{
    Sprite *sp = new Sprite(associated, "Recursos/img/Bullet.png");
    sp->SetScale(2.0f, 2.0f);
    associated.AddComponent(sp);
    associated.angleDeg = angle * 180.0f / M_PI;
    this->speed = Vec2(speed, 0).GetRotated(angle);
    Vec2 currentCenter(associated.box.x, associated.box.y);
    associated.box.SetCenter(currentCenter);
}

void Bullet::Start()
{
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

void Bullet::Update(float dt)
{
    float moveDist = speed.GetMagnitude() * dt;
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= moveDist;
    if (distanceLeft <= 0)
        associated.RequestDelete();
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) { return type == "Bullet"; }

int Bullet::GetDamage() { return damage; }

void Bullet::NotifyCollision(GameObject &other)
{
    Zombie *zombie = other.GetComponent<Zombie>();
    Character *character = other.GetComponent<Character>();
    if ((zombie && !targetsPlayer) || (character && targetsPlayer))
    {
        associated.RequestDelete();
    }
}