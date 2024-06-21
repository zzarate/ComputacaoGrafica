/**
 * Shader class
 * This class is responsible for rendering the scene
 */

#include "Shader.h"
#include "../include/glad.c"
#include <cstring>
#include <fstream>
#include <iostream>


/**
 * Constructor
 */
Shader::Shader()
{
	// Shader
	shaderProgram = 0;
}

/**
 * Create a shader program
 * @param vertexPath The path to the vertex shader
 * @param fragmentPath The path to the fragment shader
 */
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Load the vertex shader
	const char *vertexCodeC  = _loadShader(vertexPath);

	// Load the fragment shader
	const char *fragmentCodeC = _loadShader(fragmentPath);

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
 * Destructor
 */
Shader::~Shader()
{
	// Delete the shader program
	if (shaderProgram) {
		glDeleteProgram(shaderProgram);
	}
}

/**
 * Use the shader program
 */
void Shader::useShader() const
{
	glUseProgram(shaderProgram);
}

/**
 * Return the shader program ID
 */
unsigned int Shader::getShaderProgram() const
{
	return shaderProgram;
}

/**
 * Set a boolean value in the shader
 * @param name The name of the variable
 * @param value The value to set
 */
void
Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

/**
 * Set an integer value in the shader
 * @param name The name of the variable
 * @param value The value to set
 */
void
Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

/**
 * Set a float value in the shader
 * @param name The name of the variable
 * @param value The value to set
 */
void
Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

/**
 * Set a mat4 value in the shader
 * @param name The name of the variable
 * @param mat The value to set
 */
void
Shader::setVec2(const std::string &name, const glm::vec2 &value)
{
	glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

/**
 * Set a vec2 value in the shader
 * @param name The name of the variable
 * @param x The x value
 * @param y The y value
 */
void
Shader::setVec2(const std::string &name, float x, float y)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

/**
 * Set a vec3 value in the shader
 * @param name The name of the variable
 * @param value The value to set
 */
void
Shader::setVec3(const std::string &name, const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

/**
 * Set a vec3 value in the shader
 * @param name The name of the variable
 * @param x The x value
 * @param y The y value
 * @param z The z value
 */
void
Shader::setVec3(const std::string &name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

/**
 * Set a vec4 value in the shader
 * @param name The name of the variable
 * @param value The value to set
 */
void
Shader::setVec4(const std::string &name, const glm::vec4 &value)
{
	glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

/**
 * Set a vec4 value in the shader
 * @param name The name of the variable
 * @param x The x value
 * @param y The y value
 * @param z The z value
 * @param w The w value
 */
void
Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

/**
 * Set a mat4 value in the shader
 * @param name The name of the variable
 * @param mat The value to set
 */
void
Shader::setMat2(const std::string &name, const glm::mat2 &mat)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/**
 * Set a mat3 value in the shader
 * @param name The name of the variable
 * @param mat The value to set
 */
void
Shader::setMat3(const std::string &name, const glm::mat3 &mat)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/**
 * Set a mat4 value in the shader
 * @param name The name of the variable
 * @param mat The value to set
 */
void
Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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
Shader::_loadShader(const char *path)
{
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
Shader::_checkCompileErrors(unsigned int shader, const char *type)
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


