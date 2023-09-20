#include <iostream>
#include <Window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>
#include <Shader.h>

class Test : public Application
{
public:
	unsigned int VAO{ 0 }, VBO{ 0 };
	Shader shader;
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Test()
	{
		float vertices[] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -.5f, 0.0f, 1.0f, 1.0f, 0.0f,
			-.5f, -.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		};
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		shader = Shader(
			"Resource/Shader/basic_colored_shader.vert",
			"Resource/Shader/basic_colored_shader.frag"
		);
		shader.Bind();
	}
	~Test()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void OnUpdate(float deltaTime) override
	{
		if (Window::IsKeyPressed(KeyCode::Key_Escape))
			Window::Close();
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	}
	void OnRender() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Color Picker");
		ImGui::ColorEdit4("Background Color", clearColor);
		ImGui::End();
	}
};

int main()
{
	if (Window::Create())
		Window::Run(Test());
	Window::Terminate();
}