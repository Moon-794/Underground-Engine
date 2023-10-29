#include "Player.h"

#include "GLFW/glfw3.h"

Player::Player()
{
    position = glm::vec3(0.0f);
}

void Player::ProcessInputs(GLFWwindow* window, GLfloat deltaTime, bool cursorActive)
{
    const float cameraSpeed = 5;
    glm::vec3 moveDir = glm::vec3(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveDir += normalDirection;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveDir -= normalDirection;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveDir -= glm::cross(normalDirection, glm::vec3(0.0, 1.0, 0.0));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveDir += glm::cross(normalDirection, glm::vec3(0.0, 1.0, 0.0));

    if(glm::length(moveDir) > 1.0f)
        moveDir = glm::normalize(moveDir);
    
    position += moveDir * cameraSpeed * deltaTime;

    

    if(!cursorActive)
        ProcessMouseMovements(window);
}

void Player::ProcessMouseMovements(GLFWwindow* window)
{
    GLdouble xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    normalDirection.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    normalDirection.x = -(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    normalDirection = glm::normalize(normalDirection);
    normalDirection.y = 0;
}