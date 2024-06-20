//
// Created by jvzarate on 12/06/24.
//

#ifndef TRABALHOP1_WINDOW_H
#define TRABALHOP1_WINDOW_H

#include "../include/glad/glad.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:

	Renderer renderer = Renderer();

	Window();
	~Window();
	void createWindow();            // Create a window
	void updateWindow();            // Update the window
	void terminateWindow();         // Terminate the window
	GLFWwindow *getWindow();        // Return Window

private:
	GLFWwindow *window{};           // Window
	unsigned int VBO{}, VAO{};      // Vertex data
	GLint angle_location{};         // Uniforms
	GLint position_attribute{};     // Attributes
	double lastFrame = 0;           // Last frame time
	double dt = 0;                  // Delta time

	// Callbacks for the window
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	// Keyboard callback
	static void keyboardExitCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif//TRABALHOP1_WINDOW_H
