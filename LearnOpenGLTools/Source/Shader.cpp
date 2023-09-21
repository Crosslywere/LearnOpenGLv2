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
	unsigned int vs{ 0 }, fs{ 0 };
	if (vertexShaderPath != nullptr)
	{
		vs = CompileShaderFromFile(vertexShaderPath, GL_VERTEX_SHADER);
		glAttachShader(m_BufferID, vs);
	}
	if (fragmentShaderPath != nullptr)
	{
		fs = CompileShaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER);
		glAttachShader(m_BufferID, fs);
	}
	glLinkProgram(m_BufferID);
	glDeleteShader(vs);
	glDeleteShader(fs);
	CheckLinkStatus(m_BufferID);
}

Shader::~Shader()
{
	if (m_BufferID > 0) glDeleteProgram(m_BufferID);
}

void Shader::Bind() const
{
	glUseProgram(m_BufferID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform(const std::string& name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& v)
{
	glUniform3fv(GetUniformLocation(name), 1, &v[0]);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& m)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationMap.find(name) != m_UniformLocationMap.end())
	{
		return m_UniformLocationMap[name];
	}
	int loc = glGetUniformLocation(m_BufferID, name.c_str());
	if (loc == -1)
	{
		std::cout << "\033[41m\033[30mERROR::Shader\033[0m Failed to locate uniform '"
			<< name << "' in shader program." << std::endl;
	}
	m_UniformLocationMap[name] = loc;
	return loc;
}
