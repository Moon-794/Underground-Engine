#ifndef MESH_RENDERER
#define MESH_RENDERER

#include "Component.h"
#include "Mesh.h"

class MeshRenderer : public Component
{

public:

    MeshRenderer()
    {
        
    }

    std::string GetName() override
    {
        return "Mesh Renderer";
    }

    void Update() override
    {
        //Draw
    }
};

#endif