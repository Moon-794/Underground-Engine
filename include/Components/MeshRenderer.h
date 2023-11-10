#ifndef MESH_RENDERER
#define MESH_RENDERER

#include "Component.h"
#include "Mesh.h"

class MeshRenderer : public Component
{

public:

    MeshRenderer(std::string test)
    {
        std::cout << test << "\n";
        Start();
    }

    std::string GetName() override
    {
        return "Mesh Renderer";
    }

    void Update() override
    {
        //Draw
    }

private:
    
    void Start() override
    {
        //Setup mesh and stuff
        std::cout << "Mesh setup!" << "\n";
    }
};

#endif