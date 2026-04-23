#include "Face.h"
#include "GameObject.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        associated.RequestDelete();
    }
}

void Face::Update(float dt)
{
}

void Face::Render()
{
}

bool Face::Is(std::string type)
{
    return type == "Face";
}