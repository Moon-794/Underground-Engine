#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"
#include <vector>
#include <memory>
#include <vector>
#include <algorithm>
#include <glm/gtc/quaternion.hpp>

//Forward declare scene
class Scene;

class GameObject
{

public:
    GameObject(Scene& scene);

    std::string name;
    std::vector<std::shared_ptr<Component>> components;

    //Transformation properties
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    //Template for adding components, returns a pointer
    template<typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args)
    {
        std::shared_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
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
    };

    Scene& gameScene;
};

#include "Scene.h"

#endif