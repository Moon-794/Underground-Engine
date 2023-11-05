#ifndef SCENE
#define SCENE

#include "GameObject.h"
#include <iostream>
#include <vector>

class Scene
{
public:
    Scene();
    void UpdateScene();
    
    std::vector<GameObject*> gameObjects;
};

#endif