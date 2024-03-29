#ifndef MESH_RENDERER
#define MESH_RENDERER

#include "Component.h"
#include "Mesh.h"

class MeshRenderer : public Component
{

public:
    MeshRenderer(Mesh mesh, Shader* shader)
    {
        this->mesh = mesh;
        this->shader = shader;
    }

    std::string GetName() override
    {
        return "Mesh Renderer";
    }

    void Update() override
    {
        shader->use();
        glm::mat4 model(1.0f);
        shader->setMat4("model", model);

        glm::mat4 view(1.0f);
        view = gameObject->gameScene->GetView();
        shader->setMat4("view", view);

        shader->setMat4("projection", gameObject->gameScene->projection);

        mesh.Draw(*shader);
    }

private:
    Mesh mesh;
    Shader* shader;
};

#endif