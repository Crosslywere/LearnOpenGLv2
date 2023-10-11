#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <Window.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <Camera.h>
#include <Texture.h>
#include <stb_image.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

class Cubemap : public Application
{
public:
	Cubemap()
	{
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
			-.5f, -.5f, 0.5f,  0.0f,-1.0f, 0.0f
		};
		cubeVAO = new VertexArray();
		cubeVAO->Bind();
		cubeVBO = new VertexBuffer(vertices, sizeof(vertices));
		cubeVBO->Bind();
		VertexBufferLayout().Push<float>(3).Push<float>(3).Enable();
		cubeVAO->Unbind();
		cubeVBO->Unbind();
		cubeReflectionShader = new Shader("Resource/Shader/Cubemap/surface_shader.vert", "Resource/Shader/Cubemap/reflection_shader.frag");
		cubeReflectionShader->Bind();
		cubeReflectionShader->SetUniform("skybox", 0);
		cubeRefractionShader = new Shader("Resource/Shader/Cubemap/surface_shader.vert", "Resource/Shader/Cubemap/refraction_shader.frag");
		cubeRefractionShader->Bind();
		cubeRefractionShader->SetUniform("skybox", 0);
		
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		cubemapVAO = new VertexArray();
		cubemapVAO->Bind();
		cubemapVBO = new VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
		cubemapVBO->Bind();
		VertexBufferLayout().Push<float>(3).Enable();
		cubemapVAO->Unbind();
		cubemapVBO->Unbind();
		std::vector<std::string> faces = {
			"Resource/Texture/skybox/right.jpg",
			"Resource/Texture/skybox/left.jpg",
			"Resource/Texture/skybox/top.jpg",
			"Resource/Texture/skybox/bottom.jpg",
			"Resource/Texture/skybox/front.jpg",
			"Resource/Texture/skybox/back.jpg"
		};
		glGenTextures(1, &cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		int width, height, channels;
		for (int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "\033[41m\033[30mERROR::Cubemap\033[0m Failed to load texture image '" << faces[i] << "'" << std::endl;
			}
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		cubemapShader = new Shader("Resource/Shader/Cubemap/cubemap_shader.vert", "Resource/Shader/Cubemap/cubemap_shader.frag");
		cubemapShader->Bind();
		cubemapShader->SetUniform("skybox", 0);
	}
	~Cubemap()
	{
		delete cubemapVAO;
		delete cubemapVBO;
		delete cubeVAO;
		delete cubeVBO;
		delete cubeReflectionShader;
		delete cubeRefractionShader;
		glDeleteTextures(1, &cubemapTexture);
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
		glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), Window::GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Drawing the cube
		cubeVAO->Bind();
		if (useReflection)
		{
			cubeReflectionShader->Bind();
			cubeReflectionShader->SetUniform("viewPos", camera.GetPosition());
			cubeReflectionShader->SetUniform("projection", projection);
			cubeReflectionShader->SetUniform("view", view);
			cubeReflectionShader->SetUniform("model", glm::mat4(0.5f));
		}
		else
		{
			cubeRefractionShader->Bind();
			cubeRefractionShader->SetUniform("viewPos", camera.GetPosition());
			cubeRefractionShader->SetUniform("refractionIndex", refractionIndex);
			cubeRefractionShader->SetUniform("projection", projection);
			cubeRefractionShader->SetUniform("view", view);
			cubeRefractionShader->SetUniform("model", glm::mat4(0.5f));
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		cubeVAO->Unbind();
		// Drawing the skybox (cubemap)
		glDepthFunc(GL_LEQUAL);
		cubemapShader->Bind();
		cubemapShader->SetUniform("projection", projection);
		view = glm::mat4(glm::mat3(view));
		cubemapShader->SetUniform("view", view);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		cubemapVAO->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		cubemapVAO->Unbind();
		glDepthFunc(GL_LESS);
	}

	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		if (!useReflection)
		{
			ImGui::Text("Using Refraction Shader");
			ImGui::SliderFloat("Refraction Index", &refractionIndex, 1.0f, 5.0f, "%.2f");
		}
		else
		{
			ImGui::Text("Using Reflection Shader");
		}
		if (ImGui::Button("Switch Shader"))
		{
			useReflection = !useReflection;
		}
		ImGui::End();
	}
private:
	Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
	VertexArray* cubemapVAO{ nullptr };
	VertexBuffer* cubemapVBO{ nullptr };
	Shader* cubemapShader{ nullptr };
	VertexArray* cubeVAO{ nullptr };
	VertexBuffer* cubeVBO{ nullptr };
	Shader* cubeReflectionShader{ nullptr };
	Shader* cubeRefractionShader{ nullptr };
	unsigned int cubemapTexture{ 0 };
	float refractionIndex{ 1.0f };
	bool useReflection{ false };
};

#endif