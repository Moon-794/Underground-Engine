#include "Editor.h"

Editor::Editor(Scene* scene, GLFWwindow* window)
{
    this->scene = scene;

    //Setup IMGui for GLFW
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Editor::FrameStart()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Editor::DrawSceneHierarchy()
{
    ImGui::Begin("Editor");
    
    for (size_t i = 0; i < scene->gameObjects.size(); i++)
    {
        DrawGameObject(scene->gameObjects[i]);
    }
        
    ImGui::End();
}

void Editor::FrameEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::DrawGameObject(GameObject* obj)
{
    bool isExpanded = ImGui::TreeNodeEx((obj->name + " : GameObject").c_str(), ImGuiTreeNodeFlags_DefaultOpen);

    if(isExpanded)
    {
        for (size_t i = 0; i < obj->childObjects.size(); i++)
        {
            DrawGameObject(obj->childObjects[i]);
        }

        ImGui::TreePop();
    }
}

Editor::~Editor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
