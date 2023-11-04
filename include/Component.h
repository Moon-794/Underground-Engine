#ifndef COMPONENT
#define COMPONENT

#include <iostream>

class GameObject;

class Component
{
public:
    Component();
    ~Component();

    std::string name;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual std::string GetName() = 0;

    GameObject* gameObject;
};

#endif