#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(std::vector<float> vertexData, std::vector<unsigned int> indiceData, Shader* objShader)
{
    //Generate VAO, VBO and EBO and fill with data
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceData.size() * sizeof(unsigned int), &indiceData[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Calculate number of triangles
    numVertices = indiceData.size();

    //Assign Shader
    shader = objShader;
}

void Mesh::Draw(glm::mat4 projection, glm::mat4 view)
{   
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    shader->use();
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_INT, 0);
}

