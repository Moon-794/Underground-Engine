//Editor Application for creating games using the Underground Engine.
//Target platforms: Windows

//Ok so first things first the user would need to select a game to work on.
//Games arent simple, thus we need a custom folder structure that defines the source for the game application

//..
    //projectName.project <- holds various configuration settings
    //Scenes/
        //scene1.scene <- contains the structure for the objects and components
        //scene2.scene
    //Assets/
        //Models/
        //Textures/
        //Materials/
        //Components/

//And a runtime build to look like
//../
    //projectName.exe
    //.assets <-packaged asset data
    //--Player Defined Folders-- (e.g saves, mods etc)

//Will probably change later but good enough for now.
///NOTE: i really dont care if people have the art assets, so probably just obfuscate the scripts to deter people
//idk really more of late stage design choice
//
//Ok so, the primary purpose of the editor is to provide a set of tools to allow the developer to construct
//a game by building scenes full of gameobjects with components.
//While the game is in development, it will have the folder structure above, and changes made in the editor are
//saved to file.

//The editor can even preview the game, and finally build the game with the assets nicely secured
//The building part will require using a terminal in code which sounds fun

#include <iostream>
#include "engine.h"
<<<<<<< HEAD
#include "Editor/UI/imgui.h"
#include "Editor/UI/imgui_impl_glfw.h"
#include "Editor/UI/imgui_impl_opengl3.h"
#include "ProjectLoader.h"
=======
>>>>>>> main

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main()
{
    std::cout << "Underground Editor - VA_2" << "\n";
<<<<<<< HEAD

    engine ue;
    ue.Init(SCREEN_WIDTH, SCREEN_HEIGHT);

    GameObject* camera = new GameObject(ue.currentScene);
    GameObject* level = new GameObject(ue.currentScene, "Level");

    ue.currentScene->camera = camera;
    ue.currentScene->camera->addComponent<PlayerMove>(ue.window, ue.gameTime);
    ue.currentScene->camera->position = glm::vec3(0.0, -2.0, 0.0);
    
    Shader* mapShader = new Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/map.obj");
    
    level->addComponent<MeshRenderer>(map.meshes[0], mapShader);

    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(ue.window.get(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    while (!glfwWindowShouldClose(ue.window.get()))
    {
        ue.Tick();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::BeginMainMenuBar();
        ImGui::EndMainMenuBar();

        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::Begin("Underground Editor");
        ImGui::Text("Hello");
        ImGui::End();

        ImGui::SetNextWindowBgAlpha(1.0f);
        
        ImGui::Begin("Heirarchy");
        ImGui::Text("Hello");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ue.Render();
    }

    //deallocate dear-imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //Terminate GLFW
    glfwDestroyWindow(ue.window.get());
    glfwTerminate();

=======
    RunEngine();
>>>>>>> main
    return 0;
}