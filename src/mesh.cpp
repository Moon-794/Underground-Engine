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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(int), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //Calculate number of triangles
    numVertices = indiceData.size();

    //Assign Shader
    shader = objShader;
}

void Mesh::Draw(glm::mat4 projection, glm::mat4 view, bool indices)
{   
    shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model= glm::scale(model, scale);

    int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO); 
    if(indices)
        glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_INT, 0);
        else
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
