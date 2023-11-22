#ifndef SCENE
#define SCENE

#include <../glm/glm.hpp>
#include "../glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Scene
{
public:
    Scene();
    void UpdateScene();
    

    GameObject* camera;
    std::vector<GameObject*> gameObjects;

    //Camera class / component
    glm::mat4 GetView();
    glm::mat4 projection;   
    glm::mat4 view;
};

#endif