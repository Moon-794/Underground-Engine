#include "Shader.h"
#include "AssetImporter/Model.h"
#include "Scene.h"
#include "GameTime/GameTime.h"

#include "MeshRenderer.h"
#include "PlayerMove.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <memory>
#include <typeinfo>
#include <filesystem>

class engine
{
public:
    int windowWidth;
    int windowHeight;
    
    GLFWwindow* window;
    Scene currentScene;
    UE::GameTime gameTime;

    void Init();
    void Tick();
    void UpdateScene();

private:
    GLFWwindow* CreateWindow(int screenWidth, int screenHeight, std::string windowName);
};
