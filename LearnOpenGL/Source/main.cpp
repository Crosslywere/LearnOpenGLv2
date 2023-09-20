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
	float clearColor[3]{ 0.0f, 0.0f, 0.0f };
	float myColor[3]{ 1.0f, 1.0f, 1.0f };
	Shader* shaderPtr = nullptr;
	Test()
	{
		float vertices[] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-.5f, -.5f, 0.0f, 0.0f, 0.0f, 1.0f,
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
		shaderPtr = new Shader("Resource/Shader/basic_colored_shader.vert", "Resource/Shader/basic_colored_shader.frag");
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
		glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
	}
	void OnRender() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		shaderPtr->Bind();
		shaderPtr->SetVec3("uColor", myColor[0], myColor[1], myColor[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Color Picker");
		ImGui::ColorEdit3("Background Color", clearColor);
		ImGui::ColorPicker3("Shape Color", myColor);
		ImGui::End();
	}
};

int main()
{
	if (Window::Create())
		Window::Run(Test());
	Window::Terminate();
}