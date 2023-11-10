#ifndef EDITOR
#define EDITOR

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Scene.h"

class Editor
{
public:
    Editor(Scene* scene, GLFWwindow* window);
    ~Editor();
    
    void FrameStart();
    void DrawSceneHierarchy();
    void FrameEnd();

private:
    Scene* scene;
    void DrawGameObject(GameObject* obj);
};

#endif