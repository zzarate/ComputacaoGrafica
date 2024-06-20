/**
 * Renderer class
 * This class is responsible for rendering the scene
 */

#include "Renderer.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include "../include/glad.c"


/**
 * Constructor
 */
Renderer::Renderer()
{
	// Shader
	shaderProgram = 0;
	// Vertex data
	VBO = 0;
	VAO = 0;

	// Uniforms
	angle_location = 0;
	position_attribute = 0;

}

/**
 * Destructor
 */
Renderer::~Renderer()
{
	// Delete the shader program
	if (shaderProgram) {
		glDeleteProgram(shaderProgram);
	}

	// Delete the vertex buffer
	if (VBO) {
		glDeleteBuffers(1, &VBO);
	}

	// Delete the vertex array
	if (VAO) {
		glDeleteVertexArrays(1, &VAO);
	}
}


/**
 * Create a shader program
 * @param vertexPath The path to the vertex shader
 * @param fragmentPath The path to the fragment shader
 */
void
Renderer::createShader(const char* vertexPath, const char* fragmentPath)
{
	// Load the vertex shader
	const char *vertexCodeC  = _getFileContent(vertexPath);

	// Load the fragment shader
	const char *fragmentCodeC = _getFileContent(fragmentPath);

	// Create the vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCodeC, nullptr);
	glCompileShader(vertexShader);

	// Check for vertex shader compile errors
	_checkCompileErrors(vertexShader, "VERTEX");

	// Create the fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCodeC, nullptr);
	glCompileShader(fragmentShader);

	// Check for fragment shader compile errors
	_checkCompileErrors(fragmentShader, "FRAGMENT");

	// Create the shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for shader program link errors
	_checkCompileErrors(shaderProgram, "PROGRAM");

	// Delete the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/**
 * Use the shader program
 */
void
Renderer::useShader()
{
	// Use the shader program
	glUseProgram(shaderProgram);

	// Get the uniform location for the angle
	angle_location = glGetUniformLocation(shaderProgram, "angle");

	// Get the attribute location for the position
	position_attribute = glGetAttribLocation(shaderProgram, "position");

	// Set the position attribute
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(position_attribute);

	// Set the angle uniform
	glUniform1f(angle_location, 45.0f);

	// Set the color uniform
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.0f, 0.0f, 1.0f);

//	// Set the model matrix uniform
//	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//
//	// Set the view matrix uniform
//	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//	// Set the projection matrix uniform
//	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//	// Set the light position uniform
//	glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
//
//	// Set the view position uniform
//	glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
//
//	// Set the light color uniform
//	glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
//
//	// Set the object color uniform
//	glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), objectColor.x, objectColor.y, objectColor.z);
//
//	// Set the light intensity uniform
//	glUniform1f(glGetUniformLocation(shaderProgram, "lightIntensity"), lightIntensity);
//
//	// Set the ambient intensity uniform
//	glUniform1f(glGetUniformLocation(shaderProgram, "ambientIntensity"), ambientIntensity);
//
//	// Set the specular intensity uniform
//	glUniform1f(glGetUniformLocation(shaderProgram, "specularIntensity"), specularIntensity);
//
//	// Set the shininess uniform
//	glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), shininess);
//
//	// Set the light direction uniform
//	glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
//
//	// Set the light cutoff uniform
//	glUniform1f(glGetUniformLocation(shaderProgram, "lightCutoff"), lightCutoff);

}

/**
 * Set a bool uniform in the shader
 * @param name The name of the uniform
 * @param value The value to set
 */
void
Renderer::setShaderBool(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

/**
 * Set an int uniform in the shader
 * @param name The name of the uniform
 * @param value The value to set
 */
void
Renderer::setShaderInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

/**
 * Set a float uniform in the shader
 * @param name The name of the uniform
 * @param value The value to set
 */
void
Renderer::setShaderFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

/**
 * Set a mat4 uniform in the shader
 * @param name The name of the uniform
 * @param mat The mat4 to set
 */
void
Renderer::setShaderMat4(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

/**
 * Set a vec4 uniform in the shader
 * @param name The name of the uniform
 * @param vec The vec4 to set
 */
void
Renderer::setShaderVec4(const std::string& name, glm::vec4 vec)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

/**
 * Set a vec3 uniform in the shader
 * @param name The name of the uniform
 * @param vec The vec3 to set
 */
void
Renderer::setShaderVec3(const std::string& name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z);
}


/****************************************************
 * Private methods
 ****************************************************/

/**
 * Load the content of a shader file
 * @param path The path to the shader file
 * @return The content of the shader file
 */
const char *
Renderer::_getFileContent(const char *path) {
	std::ifstream vertexFile(path);
	if (!vertexFile.is_open()) {
		std::cerr << "Failed to open shader file: " << std::endl;
		return nullptr;
	}
	std::string vertexCode((std::istreambuf_iterator<char>(vertexFile)), (std::istreambuf_iterator<char>()));
	char *buffer = new char[vertexCode.size() + 1];
	strncpy(buffer, vertexCode.c_str(), vertexCode.size());
	return buffer;
}

/**
 * Check if the shader compiled successfully
 * @param shader The shader to check
 * @param type The type of shader
 */
void
Renderer::_checkCompileErrors(unsigned int shader, const char *type)
{
	// Check if the shader compiled successfully
	int success;
	char infoLog[1024];

	if (strcmp(type, "PROGRAM") != 0) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "Error compiling " << type << " shader" << std::endl;
			std::cerr << infoLog << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "Error linking " << type << " shader" << std::endl;
			std::cerr << infoLog << std::endl;
		}
	}
}


/**
 * Return the shader program ID
 */
unsigned int Renderer::getShaderProgram() const
{
	return shaderProgram;
}
