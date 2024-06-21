#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"

int main()
{

	Window window = Window();

	window.createWindow();
	glEnable(GL_DEPTH_TEST);
	Shader shader = Shader("shaders/vertex.s", "shaders/fragment.s");

	float vertices[] = {
	        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// Create the first cube
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the vertex array
	glBindVertexArray(VAO);

	// Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the vertex array
	glBindVertexArray(0);

	// Create the second cube
	unsigned int VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	// Bind the vertex array
	glBindVertexArray(VAO2);

	// Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the vertex array
	glBindVertexArray(0);

	// Render loop
	while (!glfwWindowShouldClose(window.getWindow())) {
		// Refresh the window
		window.updateWindow();

		// Use the shader program
		shader.useShader();

		// Set the color for the first cube
		shader.setVec3("objectColor", 1.0f, 0.5f, 0.41f);
		shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		// Create transformations for the first cube
		glm::mat4 model1 = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model1 = glm::scale(model1, glm::vec3(0.5f));
		model1 = glm::rotate(model1, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)window.width / (float)window.height, 0.1f, 100.0f);

		shader.setMat4("model", model1);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		// Draw the first cube
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Set the color for the second cube
		shader.setVec3("objectColor", 0.0f, 0.0f, 1.0f);

		// Create transformations for the second cube
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::scale(model2, glm::vec3(0.5f));
		model2 = glm::translate(model2, glm::vec3(1.5f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		shader.setMat4("model", model2);

		// Draw the second cube
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the buffers
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	window.terminateWindow();

	return 0;
}
