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
    std::vector<std::shared_ptr<Component>> components;

    //Template for adding components, returns a pointer
    template<typename T>
    std::unique_ptr<T> addComponent()
    {
        std::unique_ptr<T> component = std::make_unique<T>();
        component->gameObject = this;
        components.push_back(std::move(component));
        return component;
    }

    void UpdateComponents()
    {
        //Update own components
        for (size_t i = 0; i < components.size(); i++)
        {
            components[i]->Update();
        }

        //Repeat recursively for all child objects
        for (size_t i = 0; i < childObjects.size(); i++)
        {
            childObjects[i].UpdateComponents();
        }
        
    };

private:
    Scene* gameScene;
    GameObject* parent = nullptr;
    std::vector<GameObject> childObjects;
};

#include "Scene.h"

#endif