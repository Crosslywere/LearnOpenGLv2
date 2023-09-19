#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GPUBuffer.h>
#include <string>
#include <unordered_map>

class Shader : public GPUBuffer
{
public:
	Shader() = default;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader() override;
	void Bind() const override;
	void Unbind() const override;
private:
	std::unordered_map<std::string, int> m_UniformLocationMap;
};

#endif