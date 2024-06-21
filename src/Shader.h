/* @file Shader
 * @brief This file contains the class Shader
 * This class is responsible for rendering the scene
 */

#ifndef TRABALHOP1_SHADER_H
#define TRABALHOP1_SHADER_H

#include "../include/glad/glad.h"
#include "glm/detail/type_mat4x4.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


class Shader
{
public:
	Shader();
	Shader(const char *vertexPath, const char *fragmentPath);
	~Shader();

	void useShader() const;
	[[nodiscard]] unsigned int getShaderProgram() const;

	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	void setVec2(const std::string &name, const glm::vec2 &value);
	void setVec2(const std::string &name, float x, float y);
	void setVec3(const std::string &name, const glm::vec3 &value);
	void setVec3(const std::string &name, float x, float y, float z);
	void setVec4(const std::string &name, const glm::vec4 &value);
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat);
	void setMat3(const std::string &name, const glm::mat3 &mat) ;
	void setMat4(const std::string &name, const glm::mat4 &mat) ;

private:
	unsigned int shaderProgram;     // Shader

	//Load the content of a shader file
	static const char*_loadShader(const char* path);
	//Check if the shader compiled successfully
	static void _checkCompileErrors(unsigned int shader, const char* type);
};



#endif//TRABALHOP1_SHADER_H
