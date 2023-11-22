#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <../glm/glm.hpp>
#include "../glm/gtc/matrix_transform.hpp"
#include "Component.h"
#include <vector>
#include <memory>
#include <vector>
#include <algorithm>

//Forward declare scene
class Scene;

class GameObject
{

public:
    //Use this for root level objects
    GameObject(Scene* scene, std::string name = std::string("GameObject"));
    //Use this for non-root objects
    GameObject(GameObject* parent, std::string name = std::string("GameObject"));

    std::string name;
    std::vector<std::shared_ptr<Component>> components;

    //Transformation properties
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    //Template for adding components, returns a pointer
    template<typename T, typename... Args>
    std::unique_ptr<T> addComponent(Args&&... args)
    {
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
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
            childObjects[i]->UpdateComponents();
        }
        
    };

    void SetParent(GameObject* newParent);
    std::vector<GameObject*> childObjects;
    
private:
    Scene* gameScene;
    GameObject* parent = nullptr;
    
};

#include "Scene.h"

#endif