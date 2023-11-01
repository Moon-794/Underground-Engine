#include "GameObject.h"

GameObject::GameObject(Scene* scene, std::string name) : gameScene(scene)
{
    this->name = name;
    scene->gameObjects.push_back(this);
    std::cout << "Created game object\n";
}