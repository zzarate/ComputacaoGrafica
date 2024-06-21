//
// Created by jvzarate on 12/06/24.
//

#ifndef TRABALHOP1_WINDOW_H
#define TRABALHOP1_WINDOW_H

#include "../include/glad/glad.h"
#include "Shader.h"

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	const char *title   = "Trabalho Parte 1";   // Title
	int width           = 800;                  // Width
	int height          = 600;                  // Height

	Window();
	~Window();
	void createWindow();            // Create a window
	void updateWindow();            // Update the window
	void terminateWindow();         // Terminate the window
	GLFWwindow *getWindow();        // Return Window

private:
	GLFWwindow *window{};           // Window

	double lastFrame    = 0;           // Last frame time
	double deltaTime    = 0;           // Delta time

	// Callbacks for the window
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	// Keyboard callback
	static void keyboardExitCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif//TRABALHOP1_WINDOW_H
