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

const float SCREEN_WIDTH = 1280.0f;
const float SCREEN_HEIGHT = 720.0f;

GLFWwindow* CreateWindow(int screenWidth, int screenHeight, std::string windowName);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FPSCounter(float deltaTime, int& frameCount, float& timer);
void UpdateScene(Scene* scene);
void RunEngine();