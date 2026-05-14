#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"
#include <vector>
#include <memory>
#include <string>

class Component;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);

    template <typename T>
    T *GetComponent()
    {
        for (size_t i = 0; i < components.size(); i++)
        {
            T *ptr = dynamic_cast<T *>(components[i].get());
            if (ptr != nullptr)
            {
                return ptr;
            }
        }
        return nullptr;
    }

    Rect box;
    bool started;
    double angleDeg;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};

#endif