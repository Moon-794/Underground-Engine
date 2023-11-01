#ifndef SCENE
#define SCENE

#include "GameObject.h"
#include <iostream>
#include <vector>

class Scene
{
public:
    Scene();
    std::vector<GameObject*> gameObjects;
};

#endif