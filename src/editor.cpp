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
            bool isExpanded = ImGui::TreeNodeEx((scene->gameObjects[i]->name + " : GameObject").c_str(), ImGuiTreeNodeFlags_DefaultOpen);

            //Gameobject Tree Object
            if(isExpanded)
            {
                //Loop through all components in gameobject
                for (size_t j = 0; j < scene->gameObjects[i]->components.size(); j++)
                {
                    //List Component Game
                    std::shared_ptr<Component> com = scene->gameObjects[i]->components[j];
                    ImGui::Text((*com).GetName().c_str());
                }
                
                ImGui::TreePop();
            }
        }
        
        ImGui::End();
}

void Editor::FrameEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Editor::~Editor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
