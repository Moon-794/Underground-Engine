#ifndef UE_SCENE
#define UE_SCENE

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Scene
{
public:
    Scene();

    void UpdateScene();
    void SetCamera(GameObject* camera);

    void UpdateProjectionMatrix(float newWidth, float newHeight);

    GameObject& CreateGameobject();

    std::vector<std::unique_ptr<GameObject>> gameObjects;

    //Camera class / component
    glm::mat4 GetView();
    glm::mat4 projection;
    glm::mat4 view;

    GameObject* sceneCamera;
};

#endif