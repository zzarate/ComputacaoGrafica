#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Window.h"

int main()
{

	Window window       = Window();

	window.createWindow();
	window.renderer.createShader("shaders/vertex.s", "shaders/fragment.s");

	float vertices[] = {
		// positions         // normals
		 0.5f, -0.5f, 0.0f,    // bottom right
		-0.5f, -0.5f, 0.0f,    // bottom left
		 0.0f,  0.5f, 0.0f     // top
	};


	glGenBuffers(1, &window.renderer.VBO);
	glGenVertexArrays(1, &window.renderer.VAO);
	glEnableVertexAttribArray(1);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(window.renderer.VAO);

    // Bind the Vertex Buffer Object to the Vertex Array Object
	glBindBuffer(GL_ARRAY_BUFFER, window.renderer.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // THIS IS FOR THE INDICES
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Render loop
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		window.updateWindow();
	}

    window.terminateWindow();

	return 0;
}
