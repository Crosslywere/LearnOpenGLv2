#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GPUBuffer.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader : public GPUBuffer
{
public:
	Shader() = default;
	/**
	 * @brief Constructor that loads shaders and links them into a usable shader program
	 */
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	/**
	 * @brief Deletes the shader program if one was created
	 */
	~Shader() override;
	/**
	 * @brief Sets the shader as the current shader program to be used on the GPU
	 */
	void Bind() const override;
	/**
	 * @brief Removes the currently in use shader program for being active on the GPU
	 */
	void Unbind() const override;
	/**
	 * @brief Sets a uniform float value on the shader program
	 * 
	 * @param[in] name The string variable name of the uniform
	 * @param[in] v0 The float to assign the variable
	 */
	void SetUniform(const std::string& name, float v0);
	/**
	 * @brief Sets a uniform int value on the shader program
	 * 
	 * @param[in] name The string variable name of the uniform
	 * @param[in] v0 The integer to assign the variable
	 */
	void SetUniform(const std::string& name, int v0);
	/**
	 * @brief Sets a uniform vec3 value on the shader program
	 * 
	 * @param[in] name The string variable name of the uniform
	 * @param[in] v0 The float value to assign to the x component of the vec3 uniform
	 * @param[in] v1 The float value to assign to the y component of the vec3 uniform
	 * @param[in] v2 The float value to assign to the z component of the vec3 uniform
	 */
	void SetUniform(const std::string& name, float v0, float v1, float v2);
	/**
	 * @brief Sets a uniform vec3 value on the shader program
	 * 
	 * @param[in] name The string variable name of the uniform
	 * @param[in] v The vec3 data structure provided by glm
	 */
	void SetUniform(const std::string& name, const glm::vec3& v);
	/**
	 * @brief Sets a uniform mat4 value on the shader program
	 * 
	 * @param[in] name The string variable name of the uniform
	 * @param[in] m The mat4 data structure provided by glm
	 */
	void SetUniform(const std::string& name, const glm::mat4& m);
private:
	/**
	 * @brief Retrives the uniforms location from the unordered map of uniform names and values. If
	 * the uniform name hasn't been used before the location is stored for easy retrieval later.
	 */
	int GetUniformLocation(const std::string& name);
	std::unordered_map<std::string, int> m_UniformLocationMap;
};

#endif