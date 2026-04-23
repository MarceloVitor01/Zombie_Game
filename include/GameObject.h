#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Rect.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetComponent(std::string type);

    template <typename T>
    T *GetComponent()
    {
        for (auto &component : components)
        {
            T *ptr = dynamic_cast<T *>(component.get());
            if (ptr != nullptr)
            {
                return ptr;
            }
        }
        return nullptr;
    }

    Rect box;

private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
};

#endif