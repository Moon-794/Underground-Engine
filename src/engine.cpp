#include "engine.h"

typedef struct GLFWwindow GLFWwindow;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct GLFWWindowDeleter
{
    void operator()(GLFWwindow* window) const
    {
        if(window)
            glfwDestroyWindow(window);
    }
};

void engine::Init(int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;

    glfwInit();

    currentScene = std::make_shared<Scene>();
    currentScene->projection;
    gameTime = std::make_shared<UE::GameTime>();

    window = CreateWindow(windowWidth, windowHeight, "The Underground");
    if(window == nullptr)
    {
        std::cout << "ERR::Window not created.\n";
    }
}

void engine::Tick()
{
    UpdateScene();
    gameTime->CalculateDeltaTime();
}

void engine::Render()
{
    glfwSwapBuffers(window.get());
    glfwPollEvents();
}

void engine::UpdateScene()
{
    for (size_t i = 0; i < currentScene->gameObjects.size(); i++)
    {
        currentScene->gameObjects[i]->UpdateComponents();
    }
}

std::shared_ptr<GLFWwindow> engine::CreateWindow(int screenWidth, int screenHeight, std::string windowName)
{
    //Window Setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    else
    {   
        //Make window the current focus
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        //Load GLAD (needs an context)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glViewport(0, 0, screenWidth, screenHeight);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glEnable(GL_DEPTH_TEST);

        glfwSetWindowUserPointer(window, &currentScene);
        std::cout << &currentScene;

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        std::shared_ptr<GLFWwindow> shrd_window(window, GLFWWindowDeleter());
        return shrd_window;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    std::shared_ptr<Scene> scene = *static_cast<std::shared_ptr<Scene>*>(glfwGetWindowUserPointer(window));

    if(scene)
        scene->UpdateProjectionMatrix(width, height);
    else
        std::cout << "Scene not found!\n";
}

