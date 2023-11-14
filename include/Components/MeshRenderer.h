#ifndef MESH_RENDERER
#define MESH_RENDERER

#include "Component.h"
#include "Mesh.h"

class MeshRenderer : public Component
{

public:

    Shader shader;
    std::unique_ptr<Mesh> mesh;

    MeshRenderer(std::unique_ptr<Mesh> mesh, Shader& shader)
    {
        this->mesh = std::move(mesh);
        this->shader = shader;
    }

    std::string GetName() override
    {
        return "Mesh Renderer";
    }

    void Update() override
    {
        shader.use();
        shader.setMat4("projection", gameObject->gameScene->projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, gameObject->position);

        shader.setMat4("model", model);
        shader.setMat4("view", gameObject->gameScene->GetView());
        mesh->Draw(shader);
    }
};

#endif