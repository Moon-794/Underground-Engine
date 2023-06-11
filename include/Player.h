#ifndef PLAYER
#define PLAYER

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Player
{
public:
    glm::vec3 position;

    float rotationY;
    float rotationX;

    Player();

    void PositionCamera();
};

#endif