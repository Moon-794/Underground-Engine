#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Shader.h"
#include "Model.h"
#include "Player.h"
#include "Time.h"
#include "Scene.h"

#include "Components/MeshRenderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <memory>
#include <typeinfo>

#include <filesystem>

const float SCREEN_WIDTH = 1280.0f;
const float SCREEN_HEIGHT = 720.0f;

bool cursorActive = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int, char**) 
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Underground", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //Set vsync OFF for benchmarking
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);

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

    float timeElapsed = 0.0f;
    float timerLimit = 1.0f;
    float frameNum = 0;

    float deltaTime = 0.0f;

    Scene* scene = new Scene();
    GameObject gameobj = GameObject(scene, "Basic Object");

    gameobj.addComponent<MeshRenderer>();
    
    std::chrono::high_resolution_clock timer;
    using ms = std::chrono::duration<float, std::milli>;
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        auto start = timer.now();
        frameNum++;

        //Run through scene object components
        for (size_t i = 0; i < scene->gameObjects.size(); i++)
        {
            for (size_t j = 0; j < scene->gameObjects[i]->components.size(); j++)
            {
                scene->gameObjects[i]->UpdateComponents();
            }
        }
        
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Process Input From Player
        player.ProcessInputs(window, deltaTime, cursorActive);

        timeElapsed += deltaTime;

        if(timeElapsed > 1.0f)
        {
            timeElapsed = 0.0f;
            std::cout << "FPS: " << frameNum << "\n";
            frameNum = 0;
        }

        mapShader.use();
        //Get view/proj matrix for mesh drawing
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::rotate(view, -glm::radians(player.pitch), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(player.yaw), glm::vec3(0, 1, 0));
        view = glm::translate(view, player.position);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
        mapShader.setMat4("projection", projection);
        mapShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        mapShader.setMat4("model", model);
        map.Draw(mapShader);

        ImGui::Begin("Editor");
        for (size_t i = 0; i < scene->gameObjects.size(); i++)
        {
            bool isExpanded = ImGui::TreeNodeEx((scene->gameObjects[i]->name + " : GameObject").c_str(), ImGuiTreeNodeFlags_DefaultOpen);

            if(isExpanded)
            {
                for (size_t j = 0; j < scene->gameObjects[i]->components.size(); j++)
                {
                    std::shared_ptr<Component> com = scene->gameObjects[i]->components[j];
                    
                    ImGui::Text((*com).GetName().c_str());
                }
                
                ImGui::TreePop();
            }
        }
        
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

        auto stop = timer.now();

        deltaTime = std::chrono::duration_cast<ms>(stop - start).count() / 1000;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_PRESS)
    {
        cursorActive = !cursorActive;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (!cursorActive * 2));
    }
}
