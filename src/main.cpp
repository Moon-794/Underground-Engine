#include <iostream>
#include "engine.h"

int main(int argc, char** args)
{
    engine e;
    e.Init(800, 600);

    GameObject* camera = new GameObject(e.currentScene);
    GameObject* level = new GameObject(e.currentScene, "Level");

    e.currentScene->camera = camera;
    e.currentScene->camera->addComponent<PlayerMove>(e.window, e.gameTime);
    e.currentScene->camera->position = glm::vec3(0.0, -4.0, 0.0);
    
    Shader* mapShader = new Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/Map/map.obj");
    
    level->addComponent<MeshRenderer>(map.meshes[0], mapShader);

    while(!glfwWindowShouldClose(e.window.get()))
    {
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        e.Tick();
        e.Render();
    }

    return 0;
}