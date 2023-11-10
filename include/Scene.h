#ifndef SCENE
#define SCENE

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

};

#endif