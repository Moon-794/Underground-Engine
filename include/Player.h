#ifndef PLAYER
#define PLAYER

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLFW/glfw3.h"
#include <iostream>

class Player
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 normalDirection;

    Player();
    float yaw, pitch = 0;
    void ProcessInputs(GLFWwindow* window, GLfloat deltaTime, bool cursorActive);
private:
    float lastX = 400, lastY = 300;

    void ProcessMouseMovements(GLFWwindow* window);
};

#endif