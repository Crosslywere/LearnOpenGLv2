#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <Window.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

class SpotLight : public Application
{
public:
	SpotLight()
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
		vbo->Bind();
		VertexBufferLayout().Push<float>(3).Push<float>(3).Push<float>(2).Enable();
		objectShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/SpotLight/spot_light_shader.frag");
		objectDiffuse = new Texture("Resource/Texture/container2.png");
		objectDiffuse->SetSlot(0);
		objectSpecular = new Texture("Resource/Texture/container2_specular.png");
		objectSpecular->SetSlot(1);
		glEnable(GL_DEPTH_TEST);
	}
	~SpotLight()
	{
		delete vao;
		delete vbo;
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
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), Window::GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		objectShader->Bind();
		objectShader->SetUniform("uProjection", projection);
		objectShader->SetUniform("uView", view);
		objectDiffuse->Bind();
		objectShader->SetUniform("uMaterial.diffuse", 0);
		objectSpecular->Bind();
		objectShader->SetUniform("uMaterial.specular", 1);
		objectShader->SetUniform("uMaterial.shininess", shininess);
		objectShader->SetUniform("uLight.ambient", ambientAmt * lightDiffuse);
		objectShader->SetUniform("uLight.diffuse", lightDiffuse);
		objectShader->SetUniform("uLight.specular", specularAmt * lightDiffuse);
		objectShader->SetUniform("uLight.position", camera.GetPosition());
		objectShader->SetUniform("uLight.direction", camera.GetFront());
		objectShader->SetUniform("uLight.constant", 1.0f);
		objectShader->SetUniform("uLight.linear", linear);
		objectShader->SetUniform("uLight.quadratic", quadratic);
		objectShader->SetUniform("uLight.innerCutoff", glm::cos(glm::radians(innerAngle)));
		objectShader->SetUniform("uLight.outerCutoff", glm::cos(glm::radians(outerAngle)));
		objectShader->SetUniform("uViewPos", camera.GetPosition());
		static const glm::vec3 cubePositions[10] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f),
		};
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			float angle = i * 20.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objectShader->SetUniform("uModel", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		ImGui::ColorEdit3("Background Color", &clearColor[0]);
		ImGui::ColorEdit3("Light Color", &lightDiffuse[0]);
		ImGui::SliderFloat("Ambient Light Strength", &ambientAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Light Strength", &specularAmt, 0.0f, 1.0f);
		ImGui::InputFloat("Light Linear", &linear);
		ImGui::InputFloat("Light Quadratic", &quadratic);
		ImGui::SliderFloat("Inner Cutoff Angle", &innerAngle, 0.0f, 90.0f, "%.0f");
		ImGui::SliderFloat("Outer Cutoff Angle", &outerAngle, innerAngle, 90.0f, "%.0f");
		if (ImGui::Button("Reset"))
		{
			camera.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
			camera.SetPitch(0.0f);
			camera.SetYaw(-90.0f);
			lightDiffuse = glm::vec3(1.0f);
			ambientAmt = 0.1f;
			specularAmt = 0.5f;
			linear = 0.22f;
			quadratic = 0.2f;
			innerAngle = 15.0f;
			outerAngle = 25.0f;
		}
		ImGui::End();
	}
private:
	VertexArray* vao = nullptr;
	VertexBuffer* vbo = nullptr;
	Shader* objectShader = nullptr;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	Texture* objectDiffuse = nullptr;
	Texture* objectSpecular = nullptr;
	float shininess = 32.0f;
	float ambientAmt = 0.1f;
	glm::vec3 lightDiffuse = glm::vec3(1.0f);
	float specularAmt = 0.5f;
	float linear = 0.22f;
	float quadratic = 0.2f;
	float innerAngle = 15.0f;
	float outerAngle = 25.0f;
	glm::vec3 clearColor = glm::vec3(0.1f);
};

#endif