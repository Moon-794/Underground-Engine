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
#include "Editor/UI/imgui.h"
#include "Editor/UI/imgui_impl_glfw.h"
#include "Editor/UI/imgui_impl_opengl3.h"
#include "ProjectLoader.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main()
{
    std::cout << "Underground Editor - VA_2" << "\n";

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

    ImGuiStyle style = ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImVec2 imageSize;
    while (!glfwWindowShouldClose(ue.window.get()))
    {
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ue.Tick();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::SetNextWindowBgAlpha(1.0f);
        if(ImGui::Begin("Window #1"))
        {
            ImGui::Text("Hello");
        }
        ImGui::End();

        ImGui::SetNextWindowBgAlpha(1.0f);
        if(ImGui::Begin("Window #2"))
        {
            ImGui::Text("Hello");
        }
        ImGui::End();

        ImGui::SetNextWindowBgAlpha(1.0f);
        if(ImGui::Begin("Window #3"))
        {
            float gameWindowWidth = 1280;
            float gameWindowHeight = 720;

            float aspectRatio = gameWindowWidth / gameWindowHeight;

            //Image will match smallest frame dim, then scale the other size to accomadate
            float frameHeight = ImGui::GetWindowHeight();
            float frameWidth = ImGui::GetWindowWidth();

            if(frameHeight < frameWidth)
            {
                imageSize.x = frameHeight * aspectRatio;
                imageSize.y = frameHeight;
            }
            else
            {
                imageSize.x = frameWidth;
                imageSize.y = frameWidth * (1/aspectRatio);
            }

            if(frameWidth < imageSize.x)
            {
                imageSize.x = frameWidth;
                imageSize.y = frameWidth * (1/aspectRatio);
            }
            
            if(frameHeight < imageSize.y)
            {
                imageSize.y = frameHeight;
                imageSize.x = frameHeight * aspectRatio;
            }

            ImGui::Image((ImTextureID)(intptr_t)texture, imageSize, ImVec2(0, 1), ImVec2(1, 0));
        }
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

    return 0;
}