#include "engine.h"

void engine::Init()
{
    glfwInit();

    currentScene = Scene();
    gameTime = UE::GameTime();

   window = CreateWindow(windowWidth, windowHeight, "The Underground");
    if(window == nullptr)
    {
        std::cout << "ERR::Window not created.\n";
    }
}

void engine::Tick()
{
    Shader mapShader = Shader("Shaders/Basic/vertex.vs", "Shaders/Basic/fragment.fs");
    Model map = Model("Models/map.obj");
    
    currentScene.camera->addComponent<PlayerMove>(window, gameTime);
    currentScene.camera->position = glm::vec3(0.0, -2.0, 0.0);

    //Setup projection matrix and set it to the shader
    mapShader.use();
    mapShader.setMat4("projection", currentScene.projection); 

    glm::mat4 model = glm::mat4(1.0f);
    mapShader.setMat4("model", model);
    int frameCount = 0;
    float timer = 0;
    while(!glfwWindowShouldClose(window))
    {
        UpdateScene();
        gameTime.CalculateDeltaTime();
        
        mapShader.use();
        mapShader.setMat4("view", currentScene.GetView());
        map.meshes[0].Draw(mapShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}

void engine::UpdateScene()
{
    //GLFW Boilerplate
    glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (size_t i = 0; i < currentScene.gameObjects.size(); i++)
    {
        currentScene.gameObjects[i]->UpdateComponents();
    }
}

GLFWwindow* engine::CreateWindow(int screenWidth, int screenHeight, std::string windowName)
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

        return window;
    }
}

