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
	if (m_Direction.x > 0)
		m_Direction.x += (100.0f / (rand() % 100)) + 3.0f;
	if (m_Direction.x < 0)
		m_Direction.x -= (100.0f / (rand() % 100)) + 3.0f;

	if (m_Direction.y > 0)
		m_Direction.y += (100.0f / (rand() % 100)) + 3.0f;
	if (m_Direction.y < 0)
		m_Direction.y -= (100.0f / (rand() % 100)) + 3.0f;

	// Add a little bit of speed to make more difficult to return, just like real life
	m_MovementSpeed += 30.0f;
}

void Ball::Update(Paddle& paddle1, Paddle& paddle2, GLfloat& deltaTime)
{
	// Move position by direction
	m_Position += m_Direction * deltaTime * m_MovementSpeed;

	m_Direction = glm::vec3(glm::vec2(glm::normalize(m_Direction)), 0.0f);


	if (m_Direction.x == 0.0f || m_Direction.y == 0.0f)
		m_Direction = glm::vec3(0.9f, 0.4f, 0.0f);

	// It gets past either paddle
	if (m_Position.x > m_BufferWidth / 2 || m_Position.x < -m_BufferWidth / 2)
	{
		if (m_Position.x > m_BufferWidth / 2)
			paddle1.IncrScore();
		else
			paddle2.IncrScore();

		paddle1.Reset(); 
		paddle2.Reset();
		Start();
		return;
	}
	
	// It hits the ceiling
	if (m_Position.y > m_BufferHeight / 2 || m_Position.y < -m_BufferHeight / 2)
	{
		m_Direction.y = -m_Direction.y;
	
		if (m_Position.y + m_Scale.y > m_BufferHeight / 2)
			m_Position.y -= 10.0f;
		if (m_Position.y - m_Scale.y < -m_BufferHeight / 2)
			m_Position.y += 10.0f;

		SetRandomBounce();
	}

	// Paddle 1 bounces it back
	if (
		(m_Position.x - (m_Scale.x / 2)) < paddle1.GetPosition().x + (paddle1.GetScale().x / 2) &&
		(m_Position.x + (m_Scale.x / 2)) > paddle1.GetPosition().x - (paddle1.GetScale().x / 2) &&
		(m_Position.y - (m_Scale.y / 2)) < paddle1.GetPosition().y + (paddle1.GetScale().y / 2) &&
		(m_Position.y + (m_Scale.y / 2)) > paddle1.GetPosition().y - (paddle1.GetScale().y / 2)
	)
	{
		m_Direction.x = -m_Direction.x + 0.4f;
		m_Position.x += 5.0f;
		SetRandomBounce();
		paddle1.IncrSpeed(130.0f);
	}

	// Paddle 2 bounces it back
	if (
		(m_Position.x - (m_Scale.x / 2)) < paddle2.GetPosition().x + (paddle2.GetScale().x / 2) &&
		(m_Position.x + (m_Scale.x / 2)) > paddle2.GetPosition().x - (paddle2.GetScale().x / 2) &&
		(m_Position.y - (m_Scale.y / 2)) < paddle2.GetPosition().y + (paddle2.GetScale().y / 2) &&
		(m_Position.y + (m_Scale.y / 2)) > paddle2.GetPosition().y - (paddle2.GetScale().y / 2)
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
