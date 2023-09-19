#include <iostream>
#include <Window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>

static const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 color;
	void main()
	{
		color = aColor;
		gl_Position = vec4(aPos, 1.0);
	}
)";

const char* fragmentShaderSource = R"(
	#version 330 core
	in vec3 color;
	void main()
	{
		gl_FragColor = vec4(color, 1.0);
	}
)";

void CheckCompileStatus(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cout << "\033[41m\033[30mERROR::Shader\033[0m " << infoLog << std::endl;
	}
}

void CheckLinkStatus(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, 0, infoLog);
		std::cout << "\033[41m\033[30mERROR::Program\033[0m " << infoLog << std::endl;
	}
}

void ProcessInputs()
{
	if (Window::IsKeyPressed(KeyCode::Forward))
	{
		Window::Close();
	}
}

int main()
{
	if (Window::Create())
	{
		float verts[18] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-.5f, -.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
		glCompileShader(vertexShader);
		CheckCompileStatus(vertexShader);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
		glCompileShader(fragmentShader);
		CheckCompileStatus(fragmentShader);
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		CheckLinkStatus(shaderProgram);
		glUseProgram(shaderProgram);
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		while (Window::IsRunning())
		{
			Window::Poll();
			ProcessInputs();
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Creating the ImGui frame
			ImGui::NewFrame();
			ImGui::Begin("Color Picker");
			ImGui::ColorEdit4("Background Color", clearColor);
			ImGui::End();
			Window::Render();
		}

	}
	Window::Terminate();
}