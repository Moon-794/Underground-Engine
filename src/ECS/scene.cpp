#include "Scene.h"

Scene::Scene()
{
    std::cout << "Scene Created\n";
}

void Scene::UpdateScene()
{
    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        for (size_t j = 0; j < gameObjects[i]->components.size(); j++)
        {
            gameObjects[i]->UpdateComponents();
        }
    }
}