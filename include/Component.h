#ifndef COMPONENT
#define COMPONENT

#include <iostream>

class GameObject;

class Component
{
public:
    Component();
    void Update();

    GameObject* parent;
};

#endif