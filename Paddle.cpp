#include "Paddle.h"

Paddle::Paddle()
	: Object()
{
	m_MovementSpeed = 1.0f;
}

Paddle::Paddle(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation, GLfloat movementSpeed, GLint bufferHeight, GLint bufferWidth) :
	Object(mesh, position, scale, modelLocation)
{
	m_InitialMovementSpeed = movementSpeed;
	m_MovementSpeed = movementSpeed;
	m_BufferHeight = bufferHeight;
	m_BufferWidth = bufferWidth;
}

void Paddle::Reset()
{
	m_MovementSpeed = m_InitialMovementSpeed;
}

void Paddle::KeyMove(bool* keys, GLfloat& deltaTime, GLenum keyUp, GLenum keyDown)
{
	m_Velocity = m_MovementSpeed * deltaTime;

	if (keys[keyUp])
	{
		m_Position += glm::vec3(0.0f, 1.0f, 0.0f) * m_Velocity;
	}

	if (keys[keyDown])
	{
		m_Position += glm::vec3(0.0f, -1.0f, 0.0f) * m_Velocity;
	}

	if (m_Position.y > (((float) m_BufferHeight / 1.6f) - m_Scale.y))
		m_Position.y = (((float) m_BufferHeight / 1.6f) - m_Scale.y);

	if (m_Position.y < ((-(float) m_BufferHeight / 1.6f) + m_Scale.y))
		m_Position.y = ((-(float) m_BufferHeight / 1.6f) + m_Scale.y);
}

void Paddle::IncrSpeed(float speedIncr)
{
	m_MovementSpeed += speedIncr;
}

Paddle::~Paddle()
{
}
