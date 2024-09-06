#include <iostream>
#include "engine.h"

int main(int argc, char** args)
{
    Engine game;
    game.Init(1280, 720);

    GameObject& camera = game.currentScene->CreateGameobject();
    
    game.currentScene->SetCamera(&camera);

    Shader* mapShader = new Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/Map/map.obj");

    GameObject& level = game.currentScene->CreateGameobject();
    level.addComponent<MeshRenderer>(map.meshes[0], mapShader);
 
    camera.addComponent<PlayerMove>(game.window, game.gameTime);
    camera.position = glm::vec3(0.0, -4.0, 0.0);

    while(!glfwWindowShouldClose(game.window.get()))
    {
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::cout << camera.rotation.x << " " << camera.rotation.y << " " << camera.rotation.z << "\n";

        game.Tick();
        game.Render();
    }
}