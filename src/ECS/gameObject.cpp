#include "GameObject.h"

GameObject::GameObject(Scene* scene, std::string name) : gameScene(scene)
{
    this->name = name;
    scene->gameObjects.push_back(this);
}

GameObject::GameObject(GameObject* parent, std::string name)
{
    this->name = name;
    parent->childObjects.push_back(this);
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