#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Shader.h"

#include "Player.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

class Mesh
{
public:
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> _verticies, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
    void Draw(Shader &Shader);

private:
    unsigned int VAO, VBO, EBO;
    void SetupMesh();
};

#endif