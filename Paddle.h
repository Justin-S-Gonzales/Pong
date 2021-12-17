#pragma once

#include "Object.h"

#include "GLFW/glfw3.h"

class Paddle : public Object
{
private:
	GLfloat m_InitialMovementSpeed;
	GLfloat m_MovementSpeed;
	GLfloat m_Velocity;

	GLint m_BufferHeight;
	GLint m_BufferWidth;

public:
	Paddle();
	Paddle(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation, GLfloat movementSpeed, GLint bufferHeight, GLint bufferWidth);

	void Reset();

	void KeyMove(bool* m_Keys, GLfloat& deltaTime, GLenum keyUp, GLenum keyDown);

	void IncrSpeed(float speedIncr);

	~Paddle();
};

