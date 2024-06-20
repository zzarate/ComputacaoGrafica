//
// Created by jvzarate on 12/06/24.
//

#include "Window.h"

Window::Window()
= default;

Window::~Window()
= default;


/**
 * Create a window
 */
void
Window::createWindow()
{
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Set the OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	window = glfwCreateWindow(800, 600, "Trabalho Parte 1", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load the OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyboardExitCallback);

}

/**
 * Update the window
 */
void
Window::updateWindow()
{
	double currentFrame = glfwGetTime();
	dt                  = currentFrame - lastFrame;
	lastFrame           = currentFrame;


	// Clear the screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the triangle
	glUseProgram(renderer.getShaderProgram());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

}


/**
 * Process the input
 * @param window The window to process the input
 */
void
Window::terminateWindow()
{
	if (window) {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	window = nullptr;
	VBO = 0;
	VAO = 0;
	angle_location = 0;
	position_attribute = 0;

    renderer.~Renderer();
}

/**
 * @brief glfw: whenever the window size changed (by OS or user resize) this callback function executes
 * @param width The new width
 * @param height The new height
 */

void
Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

/**
 * @brief Return the window
 * @return The window
 */
GLFWwindow
*Window::getWindow() {
	return window;
}

void
Window::keyboardExitCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	//Close the window if the user presses the escape key
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
