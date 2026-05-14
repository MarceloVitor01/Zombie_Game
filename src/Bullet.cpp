#include "Bullet.h"
#include "Sprite.h"
#include "GameObject.h"
#include <cmath>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), distanceLeft(maxDistance), damage(damage)
{

    Sprite *sp = new Sprite(associated, "Recursos/img/Bullet.png");
    sp->SetScale(2.0f, 2.0f);
    associated.AddComponent(sp);

    associated.angleDeg = angle * 180.0f / M_PI;

    this->speed = Vec2(speed, 0).GetRotated(angle);

    Vec2 currentCenter(associated.box.x, associated.box.y);
    associated.box.SetCenter(currentCenter);
}

void Bullet::Update(float dt)
{
    float moveDist = speed.GetMagnitude() * dt;
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    distanceLeft -= moveDist;

    if (distanceLeft <= 0)
    {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type)
{
    return type == "Bullet";
}

int Bullet::GetDamage()
{
    return damage;
}