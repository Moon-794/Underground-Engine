#ifndef COMPONENT
#define COMPONENT

#include <iostream>

class GameObject;

class Component
{
public:
    Component();
    ~Component();

    virtual void Start() = 0;
    virtual void Update() = 0;

    GameObject* parent;
};

#endif