#include "Shader.h"
#include "Model.h"
#include "Scene.h"
#include "Editor.h"
#include "Engine/Time.h"

#include "Components/MeshRenderer.h"
#include "Components/PlayerMove.h"

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

GLFWwindow* CreateWindow(int screenWidth, int screenHeight, std::string windowName);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FPSCounter(float deltaTime, int& frameCount, float& timer);
void UpdateScene(Scene* scene);

int main(int, char**) 
{
    glfwInit();

    GLFWwindow* window = CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Underground");
    if(window == nullptr)
        return -1;

    Shader mapShader = Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/map.obj");

    Scene* scene = new Scene();
    std::unique_ptr<Editor> editor = std::make_unique<Editor>(scene, window);
    std::shared_ptr<UE::Time> gameTime = std::make_shared<UE::Time>();
    
    scene->camera->addComponent<PlayerMove>(window, gameTime);
    scene->camera->position = glm::vec3(0.0, -2.0, 0.0);

    //Setup projection matrix and set it to the shader
    mapShader.use();
    mapShader.setMat4("projection", scene->projection); 

    glm::mat4 model = glm::mat4(1.0f);
    mapShader.setMat4("model", model);
    int frameCount = 0;
    float timer = 0;
    while(!glfwWindowShouldClose(window))
    {
        UpdateScene(scene);
        
        gameTime->CalculateDeltaTime();
        FPSCounter(gameTime->GetDeltaTime(), frameCount, timer);
        
        mapShader.use();
        mapShader.setMat4("view", scene->GetView());
        map.meshes[0].Draw(mapShader);

        //You are gonna get alot more complicated soon
        editor->FrameStart();
        editor->DrawSceneHierarchy(); 
        editor->FrameEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete scene;

    //Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void UpdateScene(Scene* scene)
{
    //GLFW Boilerplate
    glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (size_t i = 0; i < scene->gameObjects.size(); i++)
    {
        scene->gameObjects[i]->UpdateComponents();
    }
}

void FPSCounter(float deltaTime, int& frameCount, float& timer)
{
    frameCount++;
        timer += deltaTime;

        if(timer > 1.0f)
        {
            std::cout << frameCount << "\n";
            frameCount = 0;
            timer = 0;
        }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_PRESS)
    {
        cursorActive = !cursorActive;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (!cursorActive * 2));
    }
}


GLFWwindow* CreateWindow(int screenWidth, int screenHeight, std::string windowName)
{
    //Window Setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    else
    {   
        //Make window the current focus
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        //Load GLAD (needs an context)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glViewport(0, 0, screenWidth, screenHeight);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(window, key_callback);
        glEnable(GL_DEPTH_TEST);

        return window;
    }
}

