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

	/**********************************************************/
	/*   TODO: IM PROGRESS OBJECTS AND SHADERS                 */
	/**********************************************************/

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

	// Create the two cubes
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


	/**********************************************************/
	/**********************************************************/

	// Render loop
	while (!glfwWindowShouldClose(window.getWindow())) {
		// Refresh the window
		window.updateWindow();

		// Use the shader program
		shader.useShader();

		/**************************************************/


		shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		// create transformations
		glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view          = glm::mat4(1.0f);
		glm::mat4 projection    = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)window.width / (float)window.height, 0.1f, 100.0f);

		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(shader.getShaderProgram(), "model");
		unsigned int viewLoc  = glGetUniformLocation(shader.getShaderProgram(), "view");
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shader.setMat4("projection", projection);

		// render the cube
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		/**************************************************/

		// Swap the buffers
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	window.terminateWindow();

	return 0;
}
