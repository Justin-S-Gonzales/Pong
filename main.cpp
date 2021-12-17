#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// For fonts
#include "ft2build.h"
#include FT_FREETYPE_H  

#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "Window.h"
#include "Shader.h"
#include "Rectangle.h"
#include "Object.h"
#include "Paddle.h"
#include "Ball.h"

// Todo: Add menu screen

int main()
{
	float width = 1024;
	float height = 720;

	// Window
	Window window(width, height);
	window.CreateWindow();

	// Shader
	Shader shader = Shader();
	shader.CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
	shader.UseShader();
	shader.Validate();

	// Projection matrix uniform
	glm::mat4 projection = glm::ortho((GLfloat)(-(window.GetBufferWidth() / 2)), (GLfloat)(window.GetBufferWidth() / 2),
		(GLfloat)(-(window.GetBufferHeight() / 2)), (GLfloat)(window.GetBufferHeight() / 2));

	GLuint uProjection = shader.GetProjectionLocation();

	glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projection));

	// Get model matrix location
	GLuint uModel = shader.GetModelLocation();

	Rectangle* rect = new Rectangle();

	Paddle* paddle1, * paddle2;
	Ball *ball;

	float positionRatio = 2.15f;
	float scaleRatio = 5.0f;
	paddle1 = new Paddle(rect, glm::vec3(-width/positionRatio, 0.0f, 0.0f), glm::vec3(20.0f, height/scaleRatio, 0.0f), uModel, 200.0f, window.GetBufferHeight(), window.GetBufferWidth());
	paddle2 = new Paddle(rect, glm::vec3(width/positionRatio, 0.0f, 0.0f), glm::vec3(20.0f, height/scaleRatio, 0.0f), uModel, 200.0f, window.GetBufferHeight(), window.GetBufferWidth());

	ball = new Ball(rect, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(15.0f, 15.0f, 0.0f), uModel, window.GetBufferWidth(), window.GetBufferHeight(), 220.0f);
	ball->Start();

	// Delta time
	GLfloat now;
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	// Main loop
	while (!window.GetShouldClose())
	{
		// Delta time
		now = glfwGetTime();
		deltaTime = now - lastTime; 
		lastTime = now;

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (window.GetKeys()[GLFW_KEY_R])
		{
			ball->Start();
		}

		ball->Update(*paddle1, *paddle2, deltaTime);
		ball->Render();

		paddle1->KeyMove(window.GetKeys(), deltaTime, GLFW_KEY_W, GLFW_KEY_S);
		paddle1->Render();

		paddle2->KeyMove(window.GetKeys(), deltaTime, GLFW_KEY_UP, GLFW_KEY_DOWN);
		paddle2->Render();

		window.SwapBuffers();
	}

	delete rect;

	delete paddle1, paddle2;

	delete ball;
}