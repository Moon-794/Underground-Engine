#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Shader.h"
#include "Mesh.h"
#include "Player.h"

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

    std::vector<float> vertices = 
    {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
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
    
    Shader myShader = Shader("Shaders/vertex.txt", "Shaders/fragment.txt");
    Mesh myMesh = Mesh(vertices, indices, &myShader);
    
    Player player = Player();
    player.position = glm::vec3(0.0, 0.0, -5.0f);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Get view/proj matrix
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, player.position);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(103.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        myMesh.position = glm::vec3(0.0, 0.0, 0.0f);
        myMesh.Draw(projection, view);

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
