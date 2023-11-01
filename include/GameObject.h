#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "Component.h"
#include <vector>
#include <memory>

//Forward declare scene
class Scene;

class GameObject
{
public:
    //Use this for root level objects
    GameObject(Scene* scene, std::string name = std::string("GameObject"));

    //Use this for non-root objects
    GameObject(GameObject* parent, std::string name = std::string("GameObject"));

    //Arbitrary Object Data
    std::string name;

    //Template for adding components, returns a pointer o
    template<typename T>
    std::unique_ptr<T> addComponent()
    {
        std::unique_ptr<T> component = std::make_unique<T>();
        component->parent = this;
        components.push_back(std::move(component));
        return component;
    }

private:
    Scene* gameScene;
    GameObject* parent = nullptr;
    std::vector<std::unique_ptr<Component>> components;
};

#include "Scene.h"

#endif