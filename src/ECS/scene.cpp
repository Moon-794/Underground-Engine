#include "Scene.h"

Scene::Scene()
{
    camera = new GameObject(this, "Camera");
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