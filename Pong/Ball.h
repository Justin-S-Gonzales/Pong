#pragma once
#include "Object.h"

#include "Paddle.h"

#include <cstdlib>
#include <time.h>

class Ball :
    public Object
{
public:
    Ball();
    Ball(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation, int bufferWidth, int bufferHeight, float movementSpeed);

    void Start();
    void Update(Paddle& paddle1, Paddle& paddle2, GLfloat& deltaTime);

    ~Ball();

private:
    int m_BufferWidth, m_BufferHeight;
    float m_InitialMovementSpeed;
    float m_MovementSpeed;

    glm::vec3 m_Direction;

    void SetRandomBounce();
};

