#include "GameObject.h"

GameObject::GameObject(Scene& scene) : gameScene(scene)
{
    std::cout << "Created Gameobject\n";

    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}