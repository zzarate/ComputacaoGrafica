/* @file Renderer
 * @brief This file contains the class Renderer
 * This class is responsible for rendering the scene
 */

#ifndef TRABALHOP1_RENDERER_H
#define TRABALHOP1_RENDERER_H

#include "../include/glad/glad.h"
#include "glm/detail/type_mat4x4.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


class Renderer
{
public:
	unsigned int VBO, VAO;          // Vertex data

	Renderer();
	~Renderer();

	void createShader(const char *vertexPath, const char *fragmentPath);
	void useShader();
	void setShaderBool(std::string name, bool value);
	void setShaderInt(const std::string& name, int value) const;
	void setShaderFloat(const std::string& name, float value) const;
	void setShaderMat4(const std::string& name, glm::mat4 mat);
	void setShaderVec4(const std::string& name, glm::vec4 vec);
	void setShaderVec3(const std::string& name, glm::vec3 vec);
	[[nodiscard]] unsigned int getShaderProgram() const;

private:
	unsigned int shaderProgram;     // Shader
	GLint angle_location;           // Uniforms
	GLint position_attribute;       // Attributes

	//Load the content of a shader file
	static const char* _getFileContent(const char* path);
	//Check if the shader compiled successfully
	static void _checkCompileErrors(unsigned int shader, const char* type);
};



#endif//TRABALHOP1_RENDERER_H
