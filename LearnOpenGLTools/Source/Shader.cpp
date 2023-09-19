#include <Shader.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>

static void CheckCompileStatus(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cout << "\033[41m\033[30mERROR::Shader\033[0m::\n" << infoLog << std::endl;
	}
}

static unsigned int CompileShaderFromFile(const char* filePath, GLenum type)
{
	std::ifstream fileStream(filePath);
	if (!fileStream.is_open())
	{
		std::cout << "\033[41m\033[30mERROR::Shader\033[0m Failed to open '" << filePath << "'" << std::endl;
		fileStream.close();
		return 0;
	}
	std::string shaderSource;
	std::string line;
	while (std::getline(fileStream, line))
	{
		shaderSource += line + "\n";
	}
	const char* sourceStr = shaderSource.c_str();
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &sourceStr, 0);
	glCompileShader(shader);
	fileStream.close();
	CheckCompileStatus(shader);
	return shader;
}

static void CheckLinkStatus(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, 0, infoLog);
		std::cout << "\033[41m\033[30mERROR::Program\033[0m::\n" << infoLog << std::endl;
	}
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	m_BufferID = glCreateProgram();
	if (vertexShaderPath != nullptr)
	{
		unsigned int vs = CompileShaderFromFile(vertexShaderPath, GL_VERTEX_SHADER);
		glAttachShader(m_BufferID, vs);
		glDeleteShader(vs);
	}
	if (fragmentShaderPath != nullptr)
	{
		unsigned int fs = CompileShaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER);
		glAttachShader(m_BufferID, fs);
		glDeleteShader(fs);
	}
	glLinkProgram(m_BufferID);
	CheckLinkStatus(m_BufferID);
}

Shader::~Shader()
{
	if (m_BufferID != 0)
		glDeleteProgram(m_BufferID);
}

void Shader::Bind() const
{
	glUseProgram(m_BufferID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
