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

//Will probably change later but good enough for now.

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <iostream>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(720, 600, "The Underground Editor", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glViewport(0, 0, 720, 600);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    return 0;
}