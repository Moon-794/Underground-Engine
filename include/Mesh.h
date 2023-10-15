#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Shader.h"

#include "Player.h"

class Mesh
{
public:
    Mesh(std::vector<float> vertexData, std::vector<unsigned int> indiceData, Shader* objShader);
    void Draw(glm::mat4 projection, glm::mat4 view, bool indices);

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    unsigned int VAO, VBO, EBO;
    unsigned int numVertices;
    Shader* shader;
};

#endif