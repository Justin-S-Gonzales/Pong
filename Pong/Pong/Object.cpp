#include "Object.h"

Object::Object()
{
	m_Mesh = new Rectangle();

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 0.0f);

	m_ModelLocation = 0;
	m_ModelMatrix = glm::mat4(1.0f);
}

Object::Object(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation)
{
	m_Mesh = mesh;
	m_Position = position;
	m_Scale = scale;
	m_ModelLocation = modelLocation;
	m_ModelMatrix = glm::mat4(1.0f);
}

void Object::Render()
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);

	glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

	m_Mesh->Render();
}

Object::~Object()
{
}
