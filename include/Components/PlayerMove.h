#ifndef PLAYER_MOVE
#define PLAYER_MOVE

#include "Component.h"
#include "GameTime.h"

class PlayerMove : public Component
{
public: 
    PlayerMove(std::shared_ptr<GLFWwindow> window, std::shared_ptr<UE::GameTime> time)
    {
        this->window = window;
        this->time = time;
    }

    std::string GetName() override
    {
        return "Player Move";
    };

    void Update() override
    {
        ProcessMovement();
        ProcessCamera();
    };

private:
    std::shared_ptr<GLFWwindow> window;
    std::shared_ptr<UE::GameTime> time;
    glm::vec3 normalDirection;

    void ProcessMovement()
    {
        const float cameraSpeed = 5;
        glm::vec3 moveDir = glm::vec3(0.0f);

        if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
            moveDir += normalDirection;
        if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
            moveDir -= normalDirection;

        if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
            moveDir -= glm::cross(normalDirection, glm::vec3(0.0, 1.0, 0.0));
        if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
            moveDir += glm::cross(normalDirection, glm::vec3(0.0, 1.0, 0.0));

        if(glm::length(moveDir) > 1.0f)
            moveDir = glm::normalize(moveDir);
    
        gameObject->position += moveDir * cameraSpeed * time.get()->GetDeltaTime();

    };

    float pitch = 0.0f;
    float yaw = 0.0f;
    float lastX = 0.0f;
    float lastY = 0.0f;

    void ProcessCamera()
    {
        GLdouble xPos = 0.0f;
        GLdouble yPos = 0.0f;
        glfwGetCursorPos(window.get(), &xPos, &yPos);

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

        gameObject->rotation = glm::vec3(pitch, yaw, 0.0f);
    };

};

#endif