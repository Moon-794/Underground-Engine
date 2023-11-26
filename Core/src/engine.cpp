#include "engine.h"

typedef struct GLFWwindow GLFWwindow;

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
    while(!glfwWindowShouldClose(window.get()))
    {
        UpdateScene();
        gameTime->CalculateDeltaTime();

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }

    
}

void engine::UpdateScene()
{
    //GLFW Boilerplate
    glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glEnable(GL_DEPTH_TEST);

        std::shared_ptr<GLFWwindow> shrd_window(window, GLFWWindowDeleter());
        return shrd_window;
    }
}

