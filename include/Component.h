#ifndef UE_COMPONENT
#define UE_COMPONENT

#include <iostream>
#include <memory>

class GameObject;

class Component
{
public:
    Component();
    ~Component();

    std::string name;

    virtual void Update() = 0;
    virtual std::string GetName() = 0;

    GameObject* gameObject;

};

#endif