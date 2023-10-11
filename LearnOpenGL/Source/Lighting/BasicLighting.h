#pragma once
#ifndef BASIC_LIGHTING_H
#define BASIC_LIGHTING_H

#include <Window.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <Camera.h>
#include <iostream>

class BasicLighting : public Application
{
public:
	BasicLighting()
	{
		// Defining the vertices (position and normal)
		float vertices[] = {
			-.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			-.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			0.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			0.5f, -.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

			-.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,
			-.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,
			0.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,
			0.5f, -.5f, -.5f,  0.0f, 0.0f,-1.0f,
			0.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,
			-.5f, 0.5f, -.5f,  0.0f, 0.0f,-1.0f,

			-.5f, 0.5f, -.5f, -1.0f, 0.0f, 0.0f,
			-.5f, -.5f, -.5f, -1.0f, 0.0f, 0.0f,
			-.5f, -.5f, 0.5f, -1.0f, 0.0f, 0.0f,
			-.5f, -.5f, 0.5f, -1.0f, 0.0f, 0.0f,
			-.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
			-.5f, 0.5f, -.5f, -1.0f, 0.0f, 0.0f,

			0.5f, 0.5f, -.5f,  1.0f, 0.0f, 0.0f,
			0.5f, -.5f, -.5f,  1.0f, 0.0f, 0.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f, 0.0f,
			0.5f, -.5f, 0.5f,  1.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
			0.5f, 0.5f, -.5f,  1.0f, 0.0f, 0.0f,

			-.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
			-.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -.5f,  0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
			-.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,

			-.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,
			-.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,
			0.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,
			0.5f, -.5f, -.5f,  0.0f,-1.0f, 0.0f,
			0.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,
			-.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f,
		};
		vao = new VertexArray();
		vao->Bind();
		vbo = new VertexBuffer(vertices, sizeof(vertices));
		vbo->Bind();
		VertexBufferLayout().Push<float>(3).Push<float>(3).Enable();
		// Loading the object's shader
		objectShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/BasicLighting/basic_phong_shader.frag");
		// Loading the light source's shader
		lightShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/basic_light_shader.frag");
		// Enabling depth testing because rendering in 3D
		glEnable(GL_DEPTH_TEST);
	}
	~BasicLighting()
	{
		delete vao;
		delete vbo;
		delete objectShader;
		delete lightShader;
	}
	void OnUpdate(float dt) override
	{
		static float xpos = Window::GetMouseXPos();
		static float ypos = Window::GetMouseYPos();

		if (Window::IsKeyPressed(Key_Escape))
			Window::Close();

		if (Window::IsKeyPressed(Key_W) || Window::IsKeyHeld(Key_W))
			camera.SetPosition(camera.GetPosition() + (camera.GetFront() * dt * movementSpeed));
		if (Window::IsKeyPressed(Key_S) || Window::IsKeyHeld(Key_S))
			camera.SetPosition(camera.GetPosition() - (camera.GetFront() * dt * movementSpeed));
		if (Window::IsKeyPressed(Key_D) || Window::IsKeyHeld(Key_D))
			camera.SetPosition(camera.GetPosition() + (camera.GetRight() * dt * movementSpeed));
		if (Window::IsKeyPressed(Key_A) || Window::IsKeyHeld(Key_A))
			camera.SetPosition(camera.GetPosition() - (camera.GetRight() * dt * movementSpeed));
		if (Window::IsKeyPressed(Key_Space) || Window::IsKeyHeld(Key_Space))
			camera.SetPosition(camera.GetPosition() + (camera.WorldUp * dt * movementSpeed));
		if (Window::IsKeyPressed(Key_LControl) || Window::IsKeyHeld(Key_LControl))
			camera.SetPosition(camera.GetPosition() - (camera.WorldUp * dt * movementSpeed));

		if (Window::IsButtonPressed(Button_Right))
		{
			Window::SetMouseMode(MouseMode::Mouse_Disabled);
			float xoffset = Window::GetMouseXPos() - xpos;
			float yoffset = ypos - Window::GetMouseYPos();
			camera.SetYaw(camera.GetYaw() + (xoffset * dt));
			camera.SetPitch(camera.GetPitch() + (yoffset * dt));
		}
		else
		{
			Window::SetMouseMode(MouseMode::Mouse_Normal);
		}
		xpos = Window::GetMouseXPos();
		ypos = Window::GetMouseYPos();
	}
	void OnRender() override
	{
		// Setting the clear color every frame (Because could be set in ImGui)
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		// Clearing the color and depth buffer bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Recalculating the projection matrix every frame (Because fov could be changed by ImGui)
		glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), Window::GetAspectRatio(), 0.1f, 100.0f);
		// Constructing the view matrix (The view's transform)
		glm::mat4 view = camera.GetViewMatrix();

		vao->Bind();
		objectShader->Bind();

		objectShader->SetUniform("uProjection", projection);
		objectShader->SetUniform("uView", view);
		objectShader->SetUniform("uModel", glm::mat4(1.0f));
		objectShader->SetUniform("uObjectColor", objectColor);
		objectShader->SetUniform("uLightPos", lightPos);
		objectShader->SetUniform("uViewPos", camera.GetPosition());
		objectShader->SetUniform("uLightColor", lightColor);
		objectShader->SetUniform("uShininess", shininess * 64.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Constructing the model matrix (model's translation, rotation and scale)
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader->Bind();
		lightShader->SetUniform("uProjection", projection);
		lightShader->SetUniform("uView", view);
		lightShader->SetUniform("uModel", model);
		lightShader->SetUniform("uColor", lightColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		ImGui::Text("Hold the right mouse button to move the camera\n"
					"Use W, A, S, D, Space and Left Control for movement\n"
					"Escape closes the application");
		ImGui::ColorEdit3("Background Color", &clearColor[0]);
		ImGui::ColorEdit3("Object Diffuse", &objectColor[0]);
		ImGui::ColorEdit3("Light Color", &lightColor[0]);
		ImGui::SliderFloat("Shininess", &shininess, 0.0f, 1.0f, "%.1f");
		ImGui::SliderFloat("FOV", &camera.FOV, 45.0f, 90.0f, "%.1f");
		if (ImGui::Button("Reset"))
		{
			clearColor = glm::vec3(0.0f);
			objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
			lightColor = glm::vec3(1.0f);
			shininess = 0.5f;
			// Resetting the camera's data
			camera.FOV = 60.0f;
			camera.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
			camera.SetPitch(0.0f);
			camera.SetYaw(-90.0f);
		}
		ImGui::End();
	}
private:
	VertexArray* vao = nullptr;
	VertexBuffer* vbo = nullptr;
	Shader* objectShader = nullptr;
	Shader* lightShader = nullptr;
	glm::vec3 clearColor = glm::vec3(0.0f);
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);
	glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
	float shininess = 0.5f;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float movementSpeed = 2.5f;
};

#endif