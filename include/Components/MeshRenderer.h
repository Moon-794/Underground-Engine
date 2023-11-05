#ifndef MESH_RENDERER
#define MESH_RENDERER

#include "Component.h"

class MeshRenderer : public Component
{
public:

    std::string GetName() override
    {
        return "Mesh Renderer";
    }

    void Start() override
    {

    }

    void Update() override
    {
        //Draw
    }
};

#endif