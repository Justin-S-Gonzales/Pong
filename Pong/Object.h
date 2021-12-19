#pragma once

#include "Rectangle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Object
{
protected:
	Mesh* m_Mesh;

	glm::vec3 m_Position;
	glm::vec3 m_Scale;

	GLuint m_ModelLocation;
	glm::mat4 m_ModelMatrix;

public:
	Object();
	Object(Mesh* mesh, glm::vec3 position, glm::vec3 scale, GLuint modelLocation);

	void Render();

	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 GetScale() { return m_Scale; }

	~Object();
};

