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


        model = glm::translate(model, gameObject->position);
        model = glm::rotate(model, gameObject->rotation.x, glm::vec3(0, 1, 0));
        model = glm::scale(model, gameObject->scale);
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