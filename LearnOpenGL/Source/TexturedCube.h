#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <Window.h>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Texture.h>

#include <glad/glad.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class TexturedCube : public Application
{
public:
	TexturedCube()
		: clearColor{ glm::vec3(0.1f, 0.2f, 0.4f) }
	{
		float vertices[] = {
			-.5f, 0.5f, 0.5f,  0.0f, 1.0f,
			-.5f, -.5f, 0.5f,  0.0f, 0.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 1.0f,

			-.5f, 0.5f, -.5f,  0.0f, 0.0f,
			-.5f, -.5f, -.5f,  0.0f, 1.0f,
			0.5f, -.5f, -.5f,  1.0f, 1.0f,
			0.5f, -.5f, -.5f,  1.0f, 1.0f,
			0.5f, 0.5f, -.5f,  1.0f, 0.0f,
			-.5f, 0.5f, -.5f,  0.0f, 0.0f,

			-.5f, 0.5f, -.5f,  0.0f, 1.0f,
			-.5f, -.5f, -.5f,  0.0f, 0.0f,
			-.5f, -.5f, 0.5f,  1.0f, 0.0f,
			-.5f, -.5f, 0.5f,  1.0f, 0.0f,
			-.5f, 0.5f, 0.5f,  1.0f, 1.0f,
			-.5f, 0.5f, -.5f,  0.0f, 1.0f,

			0.5f, 0.5f, -.5f,  0.0f, 0.0f,
			0.5f, -.5f, -.5f,  0.0f, 1.0f,
			0.5f, -.5f, 0.5f,  1.0f, 1.0f,
			0.5f, -.5f, 0.5f,  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,  1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  0.0f, 0.0f,

			-.5f, 0.5f, 0.5f,  0.0f, 0.0f,
			-.5f, 0.5f, -.5f,  1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  1.0f, 1.0f,
			0.5f, 0.5f, -.5f,  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 0.0f,

			-.5f, -.5f, 0.5f,  0.0f, 0.0f,
			-.5f, -.5f, -.5f,  1.0f, 0.0f,
			0.5f, -.5f, -.5f,  1.0f, 1.0f,
			0.5f, -.5f, -.5f,  1.0f, 1.0f,
			0.5f, -.5f, 0.5f,  0.0f, 1.0f,
			-.5f, -.5f, 0.5f,  0.0f, 0.0f,
		};
		vao = new VertexArray();
		vao->Bind();
		vbo = new VertexBuffer(vertices, sizeof(vertices));
		vbo->Bind();
		VertexBufferLayout().Push<float>(3).Push<float>(2).Enable();
		shader = new Shader("Resource/Shader/TexturedCube/cube_shader.vert", "Resource/Shader/TexturedCube/cube_shader.frag");
		shader->Bind();
		texture = new Texture("Resource/Texture/container.jpg");
		texture->Bind();
		glEnable(GL_DEPTH_TEST);
	}
	~TexturedCube()
	{
		delete vao;
		delete vbo;
		delete shader;
	}
	void OnUpdate(float dt) override
	{
		if (Window::IsKeyPressed(Key_Escape))
			Window::Close();

		if (drawLine)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	}
	void OnRender() override
	{
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), Window::GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->SetUniform("uMVP", projection * model);
		shader->SetUniform("uTexture2D", 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		ImGui::ColorEdit3("Clear Color", &clearColor[0]);
		ImGui::SliderFloat("Angle", &angle, -360.0f, 360.0f, "%.0f");
		ImGui::Checkbox("Draw Line", &drawLine);
		ImGui::End();
	}
private:
	VertexArray* vao;
	VertexBuffer* vbo;
	Shader* shader;
	Texture* texture;
	glm::vec3 clearColor;
	float angle{ 0.0f };
	bool drawLine = false;
};

#endif