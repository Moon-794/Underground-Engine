#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Shader.h"
#include "Model.h"
#include "Player.h"
#include "Time.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>

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

    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    
    Player player = Player();
    player.position = glm::vec3(0.0f, -2.0f, 0.0f);

    Shader mapShader = Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/map.obj");

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
        mapShader.setMat4("projection", projection);
        mapShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        
        mapShader.use();
        mapShader.setMat4("model", model);
        map.Draw(mapShader);

        std::cout << player.position.x << " " << player.position.y << " " << player.position.z << "\n";

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
