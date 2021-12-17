#include "Ball.h"

Ball::Ball() : Object()
{
	m_MovementSpeed = 1.0f;
}

Ball::Ball(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation, int bufferWidth, int bufferHeight, float movementSpeed)
	: Object(mesh, position, scale, modelLocation)
{
	m_BufferWidth = bufferWidth;
	m_BufferHeight = bufferHeight;
	m_InitialMovementSpeed = movementSpeed;
	m_MovementSpeed = 1.0f;
}

void Ball::Start()
{
	srand(time(NULL));

	float randNum1 = (float) (rand() % 100);
	float randNum2 = (float) (rand() % 100);

	if (rand() % 10 > 5)
	{
		randNum1 = -randNum1;
	}

	if (rand() % 10 > 5)
	{
		randNum2 = -randNum2;
	}

	m_MovementSpeed = m_InitialMovementSpeed;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

	m_Direction = glm::vec3(randNum1, randNum2, 0.0f);

	if (abs(m_Direction.y) > abs(m_Direction.x))
	{
		float temp = m_Direction.y;
		m_Direction.x = temp;
		m_Direction.y = m_Direction.x;
	}

	m_Direction = glm::normalize(m_Direction);
}

void Ball::SetRandomBounce()
{
	// Bounces off in random direction
	if (m_Direction.x > 0 && m_Direction.y > m_Direction.x)
		m_Direction.x += 10.0f / ((rand() % 50) + 3.0f);

	else if (m_Direction.x < 0 && m_Direction.y > m_Direction.x)
		m_Direction.x -= 10.0f / ((rand() % 50) + 3.0f);

	if (m_Direction.y > 0 && m_Direction.x > m_Direction.y)
		m_Direction.y += 5.0f / ((rand() % 50 ) + 3.0f);

	else if (m_Direction.y < 0 && m_Direction.x > m_Direction.y)
		m_Direction.y -= 5.0f / ((rand() % 50) + 3.0f);

	// Add a little bit of speed to make more difficult to return, just like real life
	m_MovementSpeed += 12.0f;
}

void Ball::Update(Paddle& paddle1, Paddle& paddle2, GLfloat& deltaTime)
{
	// Move position by direction
	m_Position += m_Direction * deltaTime * m_MovementSpeed;

	// It gets past either paddle
	if (m_Position.x > m_BufferWidth / 2|| m_Position.x < -m_BufferWidth / 2)
	{
		paddle1.Reset(); 
		paddle2.Reset();
		Start();
		return;
	}
	
	// It hits the ceiling
	if (m_Position.y > m_BufferHeight / 2 || m_Position.y < -m_BufferHeight / 2)
	{
		m_Direction.y = -m_Direction.y;
	}

	// Paddle 1 bounces it back
	if (
		(m_Position.x) < (paddle1.GetPosition().x + paddle1.GetScale().x) && 
		(m_Position.x) > (paddle1.GetPosition().x - paddle1.GetScale().x) &&
		(m_Position.y) < (paddle1.GetPosition().y + paddle1.GetScale().y) &&
		(m_Position.y) > (paddle1.GetPosition().y - paddle1.GetScale().y)
		)
	{
		m_Direction.x = -m_Direction.x + 0.4f;
		m_Position.x += 5.0f;
		SetRandomBounce();
		paddle1.IncrSpeed(130.0f);
	}

	// Paddle 2 bounces it back
	if (
		(m_Position.x) < (paddle2.GetPosition().x + paddle2.GetScale().x) &&
		(m_Position.x) > (paddle2.GetPosition().x - paddle2.GetScale().x) &&
		(m_Position.y) < (paddle2.GetPosition().y + paddle2.GetScale().y) &&
		(m_Position.y) > (paddle2.GetPosition().y - paddle2.GetScale().y)
		)
	{
		m_Direction.x = -m_Direction.x - 0.4f;
		m_Position.x -= 5.0f;
		SetRandomBounce();
		paddle2.IncrSpeed(130.0f);
	}

}

Ball::~Ball()
{
}
