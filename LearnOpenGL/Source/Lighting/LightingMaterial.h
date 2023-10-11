#pragma once
#ifndef LIGHTING_MATERIAL_H
#define LIGHTING_MATERIAL_H

#include <Window.h>
#include <glad/glad.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Camera.h>
#include <imgui.h>

class LightingMaterial : public Application
{
public:
	LightingMaterial()
	{
		float vertices[] = {
			-.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			-.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			0.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			0.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,

			-.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
			-.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
			0.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
			0.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
			0.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
			-.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,

			-.5f, 0.5f, -.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
			-.5f, -.5f, -.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
			-.5f, -.5f, 0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
			-.5f, -.5f, 0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
			-.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
			-.5f, 0.5f, -.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

			0.5f, 0.5f, -.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
			0.5f, -.5f, -.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

			-.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
			-.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
			0.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

			-.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
			-.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
			0.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
			0.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
			0.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
			-.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
		};
		vao = new VertexArray();
		vao->Bind();
		vbo = new VertexBuffer(vertices, sizeof(vertices));
		VertexBufferLayout().Push<float>(3).Push<float>(3).Push<float>(2).Enable();
		lightShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/basic_light_shader.frag");
		objectShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/LightingMaterial/material_phong_shader.frag");

		objectDiffuse = new Texture("Resource/Texture/container2.png");
		objectDiffuse->SetSlot(0);
		objectSpecular = new Texture("Resource/Texture/container2_specular.png");
		objectSpecular->SetSlot(1);
		glEnable(GL_DEPTH_TEST);
	}

	~LightingMaterial()
	{
		delete vao;
		delete vbo;
		delete lightShader;
		delete objectShader;
		delete objectDiffuse;
		delete objectSpecular;
	}

	void OnUpdate(float dt) override
	{
		static float mouseX = Window::GetMouseXPos();
		static float mouseY = Window::GetMouseYPos();
		if (Window::IsKeyPressed(Key_Escape))
			Window::Close();

		if (Window::IsKeyPressed(Key_W) || Window::IsKeyHeld(Key_W))
			camera.SetPosition(camera.GetPosition() + (camera.GetFront() * dt));
		if (Window::IsKeyPressed(Key_S) || Window::IsKeyHeld(Key_S))
			camera.SetPosition(camera.GetPosition() - (camera.GetFront() * dt));
		if (Window::IsKeyPressed(Key_D) || Window::IsKeyHeld(Key_D))
			camera.SetPosition(camera.GetPosition() + (camera.GetRight() * dt));
		if (Window::IsKeyPressed(Key_A) || Window::IsKeyHeld(Key_A))
			camera.SetPosition(camera.GetPosition() - (camera.GetRight() * dt));
		if (Window::IsKeyPressed(Key_Space) || Window::IsKeyHeld(Key_Space))
			camera.SetPosition(camera.GetPosition() + (camera.WorldUp * dt));
		if (Window::IsKeyPressed(Key_LControl) || Window::IsKeyHeld(Key_LControl))
			camera.SetPosition(camera.GetPosition() - (camera.WorldUp * dt));

		if (Window::IsButtonPressed(Button_Right))
		{
			Window::SetMouseMode(MouseMode::Mouse_Disabled);
			float xoffset = Window::GetMouseXPos() - mouseX;
			float yoffset = mouseY - Window::GetMouseYPos();
			camera.SetYaw(camera.GetYaw() + (xoffset * dt));
			camera.SetPitch(camera.GetPitch() + (yoffset * dt));
		}
		else
		{
			Window::SetMouseMode(MouseMode::Mouse_Normal);
		}
		mouseX = Window::GetMouseXPos();
		mouseY = Window::GetMouseYPos();
	}

	void OnRender() override
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), Window::GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		vao->Bind();
		objectShader->Bind();
		objectShader->SetUniform("uProjection", projection);
		objectShader->SetUniform("uView", view);
		objectShader->SetUniform("uModel", model);
		objectShader->SetUniform("uViewPos", camera.GetPosition());
		objectDiffuse->Bind();
		objectShader->SetUniform("uMaterial.diffuse", 0);
		objectSpecular->Bind();
		objectShader->SetUniform("uMaterial.specular", 1);
		objectShader->SetUniform("uMaterial.shininess", shininess);
		objectShader->SetUniform("uLight.position", lightPos);
		objectShader->SetUniform("uLight.ambient", ambientAmt * lightDiffuse);
		objectShader->SetUniform("uLight.diffuse", lightDiffuse);
		objectShader->SetUniform("uLight.specular", specularAmt * lightDiffuse);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader->Bind();
		lightShader->SetUniform("uProjection", projection);
		lightShader->SetUniform("uView", view);
		lightShader->SetUniform("uModel", model);
		lightShader->SetUniform("uColor", lightDiffuse);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		ImGui::ColorEdit3("Background Color", &clearColor[0]);
		ImGui::ColorEdit3("Light Color", &lightDiffuse[0]);
		ImGui::SliderFloat("Light Ambient Amount", &ambientAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Light Specular Amount", &specularAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Shininess", &shininess, 2.0f, 128.0f, "%.0f");
		if (ImGui::Button("Reset"))
		{
			camera.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
			camera.SetPitch(0.0f);
			camera.SetYaw(-90.0f);
			ambientAmt = 0.1f;
			specularAmt = 0.5f;
			shininess = 32.0f;
			clearColor = glm::vec3(0.0f);
		}
		ImGui::End();
	}
private:
	VertexArray* vao = nullptr;
	VertexBuffer* vbo = nullptr;
	Shader* lightShader = nullptr;
	Shader* objectShader = nullptr;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	Texture* objectDiffuse = nullptr;
	Texture* objectSpecular = nullptr;
	float shininess = 32.0f;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	float ambientAmt = 0.1f;
	glm::vec3 lightDiffuse = glm::vec3(1.0f);
	float specularAmt = 0.5f;
	glm::vec3 clearColor = glm::vec3(0.0f);
};

#endif