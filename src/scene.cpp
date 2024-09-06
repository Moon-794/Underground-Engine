#include "Scene.h"

Scene::Scene()
{
    projection = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
}

GameObject& Scene::CreateGameobject()
{
    std::unique_ptr<GameObject> object = std::make_unique<GameObject>(*this);
    GameObject& ref = *object;
    
    gameObjects.push_back(std::move(object));

    return ref;
}

void Scene::SetCamera(GameObject* camera)
{
   sceneCamera = camera;
}

void Scene::UpdateProjectionMatrix(float newWidth, float newHeight)
{
    projection = glm::perspective(glm::radians(90.0f), newWidth / newHeight, 0.1f, 100.0f);
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

glm::mat4 Scene::GetView()
{
    view = glm::mat4(1.0f);
    view = glm::rotate(view, -glm::radians(sceneCamera->rotation.x), glm::vec3(1, 0, 0));
    view = glm::rotate(view, glm::radians(sceneCamera->rotation.y), glm::vec3(0, 1, 0));
    view = glm::translate(view, sceneCamera->position);

    return view;
}