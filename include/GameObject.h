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
    void addComponent()
    {
        T component = T();
        components.push_back(&component);
    }
};

#endif