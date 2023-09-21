#include <iostream>
#include <Window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp>

class Test : public Application
{
public:
	unsigned int VAO{ 0 }, VBO{ 0 };
	glm::vec3 clearColor = glm::vec3(0.0f);
	glm::vec3 myColor = glm::vec3(1.0f);
	Shader* shader;
	bool editMode = true;
	float zoom = 1.0f;
	float scale = 100.0f;
	Test()
	{
		float vertices[] = {
			0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.5f, 1.0f,
			0.5f, -.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
			-.5f, -.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		};
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		shader = new Shader("Resource/Shader/basic_colored_shader.vert", "Resource/Shader/basic_colored_shader.frag");
	}
	~Test()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		delete shader;
	}
	void OnUpdate(float deltaTime) override
	{
		if (Window::IsKeyPressed(Key_Escape))
			Window::Close();
		if (Window::IsKeyPressed(Key_F))
			editMode = true;
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	}
	void OnRender() override
	{
		float ar = Window::GetAspectRatio();
		float w = (ar * Window::GetWidth()) * zoom;
		float h = (ar * Window::GetHeight()) * zoom;
		glm::mat4 projection = glm::ortho(-w, w, -h, h);
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
		glClear(GL_COLOR_BUFFER_BIT);
		shader->Bind();
		shader->SetUniform("uColor", myColor);
		shader->SetUniform("uMVP", projection * model);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	void OnRenderImGui() override
	{
		if (editMode)
		{
			ImGui::Begin("Edit Window", &editMode);
			ImGui::ColorPicker3("Background Color", &clearColor[0]);
			ImGui::ColorPicker3("Shape Color", &myColor[0]);
			ImGui::SliderFloat("Zoom", &zoom, 1.0f, 0.001f);
			ImGui::SliderFloat("Scale", &scale, 1.0f, 100.0f);
			ImGui::End();
		}
	}
};

int main()
{
	if (Window::Create())
		Window::Run(Test());
	Window::Terminate();
}