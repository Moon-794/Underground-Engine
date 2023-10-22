

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Time.h"
#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int, char**) 
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "The Underground", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::vector<float> vertices = 
    {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    std::vector<unsigned int> indices = 
    {
        0, 1, 3,
        1, 2, 3
    };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    
    Shader myShader = Shader("Shaders/vertex.vs", "Shaders/fragment.fs");
    Shader lightingShader = Shader("Shaders/vertexLighting.vs", "Shaders/fragLighting.fs");
    Mesh myMesh = Mesh(vertices, indices, &myShader);
    myMesh.position = glm::vec3(0.0, 0.0, 0.0f);
    myMesh.scale = glm::vec3(5, 0.1f, 5);

    Mesh lightMesh = Mesh(vertices, indices, &lightingShader);
    lightMesh.position = glm::vec3(0.0f, 0.0f, 0.0f);
    lightMesh.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    
    Player player = Player();
    player.position = glm::vec3(0.0, -1.0, 0.0f);

    Texture texture = Texture("Textures/container2.png");
    Texture textureSpecular = Texture("Textures/container2_specular.png");

    unsigned int lightVAO;
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, myMesh.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myMesh.EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Process Input From Player
        player.ProcessInputs(window, 0.01f);

        //Get view/proj matrix for mesh drawing
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::rotate(view, -glm::radians(player.pitch), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(player.yaw), glm::vec3(0, 1, 0));
        view = glm::translate(view, player.position);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::vec3 cameraFront = glm::vec3(1);
        cameraFront.z = cos(glm::radians(player.yaw)) * cos(glm::radians(player.pitch));
        cameraFront.x = -(sin(glm::radians(player.yaw)) * cos(glm::radians(player.pitch)));
        cameraFront.y = sin(-glm::radians(player.pitch));

        myShader.use();
        myShader.setVec3("viewPos", -player.position);
        myShader.setVec3("light.position", -player.position);
        myShader.setVec3("light.direction",  cameraFront);
        myShader.setFloat("light.cutOff", glm::cos(glm::radians(15.0f)));
        myShader.setVec3("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
        myShader.setVec3("light.diffuse",  glm::vec3(0.7f, 0.7f, 0.5f));
        myShader.setVec3("light.specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        
        //myShader.setFloat("light.cutOff",glm::cos(glm::radians(12.5f)));
        myShader.setFloat("light.constant", 1.0f);
        myShader.setFloat("light.linear",  0.03f);
        myShader.setFloat("light.quadratic",  0.015f);

        myShader.setInt("material.diffuse", 0);
        myShader.setInt("material.specular", 1);
        myShader.setVec3("material.specular", glm::vec3(0.50196078f, 0.50196078f, 0.50196078f));
        myShader.setFloat("material.shininess", 32.0f);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.ID); 

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureSpecular.ID); 

        myMesh.Draw(projection, view, false);

        //lightMesh.Draw(projection, view, false);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
