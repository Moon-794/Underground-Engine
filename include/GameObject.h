#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "Scene.h"
#include "Component.h"

class GameObject
{
public:
    GameObject();

    std::vector<Component*> components;
    
    template<typename T>
    T* addComponent()
    {
        T* component = new T();
        component->parent = this;
        components.push_back(component);

        return component;
    }
};

#endif