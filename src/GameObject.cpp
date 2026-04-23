#include "GameObject.h"
#include <algorithm>

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    components.clear();
}

void GameObject::Update(float dt)
{
    for (auto &component : components)
    {
        component->Update(dt);
    }
}

void GameObject::Render()
{
    for (auto &component : components)
    {
        component->Render();
    }
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
    auto it = std::remove_if(components.begin(), components.end(),
                             [&](const std::unique_ptr<Component> &p)
                             { return p.get() == cpt; });

    if (it != components.end())
    {
        components.erase(it, components.end());
    }
}

Component *GameObject::GetComponent(std::string type)
{
    for (auto &component : components)
    {
        if (component->Is(type))
        {
            return component.get();
        }
    }
    return nullptr;
}