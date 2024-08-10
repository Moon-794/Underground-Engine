#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<Scene>& scene, std::string name)
{
    this->name = name;
    this->gameScene = scene;
    this->gameScene->gameObjects.push_back(this);

    position = glm::vec3(0);
}

GameObject::GameObject(GameObject* parent, std::string name) : gameScene(parent->gameScene)
{
    this->name = name;
    parent->childObjects.push_back(this);

    position = glm::vec3(0);
}

void GameObject::SetParent(GameObject* newParent)
{
    //Remove gameobject from previous vector
    if(parent == nullptr)
    {
        auto it = std::find(gameScene->gameObjects.begin(), gameScene->gameObjects.end(), this);
        gameScene->gameObjects.erase(it);
    }
    else
    {
        auto it = std::find(parent->childObjects.begin(), parent->childObjects.end(), this);
        parent->childObjects.erase(it);
    }

    //Reassign to parent
    parent = newParent;
    parent->childObjects.push_back(this);
}