#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "Component.h"
#include <vector>

//Forward declare scene
class Scene;

class GameObject
{
public:
    GameObject(Scene* scene, std::string name = std::string("GameObject"));
    std::vector<Component*> components;
    std::string name;

    template<typename T>
    T* addComponent()
    {
        T* component = new T();
        component->parent = this;
        components.push_back(component);

        return component;
    }

private:
    Scene* gameScene;
};

#include "Scene.h"

#endif