#include "Shader.h"
#include "Model.h"
#include "Player.h"
#include "Scene.h"
#include "Editor.h"
#include "Engine/Time.h"

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
    glEnable(GL_DEPTH_TEST);
    
    Player player = Player();
    player.position = glm::vec3(0.0f, -2.0f, 0.0f);

    Shader mapShader = Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/map.obj");

    Scene* scene = new Scene();
    std::unique_ptr<Editor> editor = std::make_unique<Editor>(scene, window);
    std::unique_ptr<UE::Time> gameTime = std::make_unique<UE::Time>();
    
    GameObject* gameobj = new GameObject(scene, "Basic Object");
    gameobj->addComponent<MeshRenderer>();
    scene->camera->SetParent(gameobj);

    //Setup projection matrix and set it to the shader
    mapShader.use();
    mapShader.setMat4("projection", scene->projection); 

    glm::mat4 model = glm::mat4(1.0f);
    mapShader.setMat4("model", model);

    while(!glfwWindowShouldClose(window))
    {   
        //Input system and Time system
        player.ProcessInputs(window, gameTime->GetDeltaTime(), cursorActive);
        gameTime->CalculateDeltaTime();

        //GLFW Boiler
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //store appropriate shaders in meshrenderer?
        mapShader.use();

        //Better approach is make a movement component and set camera values within that script
        scene->camera->rotation = glm::vec3(player.pitch, player.yaw, 0);
        scene->camera->position = player.position;

        ///Shader stuff
        mapShader.setMat4("view", scene->GetView());
        //Meshrenderer component should call this
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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_PRESS)
    {
        cursorActive = !cursorActive;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (!cursorActive * 2));
    }
}
