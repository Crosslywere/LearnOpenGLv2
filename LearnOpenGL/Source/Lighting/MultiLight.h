#pragma once
#ifndef MULTI_LIGHT_H
#define MULTI_LIGHT_H

#include <Window.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Texture.h>
#include <Shader.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

class MultiLight : public Application
{
public:
	MultiLight()
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
		lightShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/basic_light_shader.frag");
		objectShader = new Shader("Resource/Shader/Lighting/basic_shader.vert", "Resource/Shader/Lighting/MultiLight/multi_light_shader.frag");
		objectDiffuse = new Texture("Resource/Texture/container2.png", 0);
		objectSpecular = new Texture("Resource/Texture/container2_specular.png", 1);
		// Setting up the directional light
		directionalLight.diffuse = glm::vec3(0.4f, 0.4f, 0.8f);
		directionalLight.direction = glm::vec3(1.2f, -1.0f, -2.0f);
		// Setting up the point lights
		glm::vec3 pointLightPositions[4] = {
			glm::vec3( 0.7f,  0.2f,  2.0f),
			glm::vec3( 2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3( 0.0f,  0.0f, -3.0f),
		};
		for (int i = 0; i < 4; i++)
		{
			pointLights[i].position = pointLightPositions[i];
			pointLights[i].diffuse = glm::vec3(0.4f, 0.2f, 0.1f);
			pointLights[i].linear = 0.22f;
			pointLights[i].quadratic = 0.20f;
		}
		glEnable(GL_DEPTH_TEST);
	}
	~MultiLight()
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
		objectShader->Bind();
		objectShader->SetUniform("uProjection", projection);
		objectShader->SetUniform("uView", view);
		// Material uniform
		objectDiffuse->Bind();
		objectShader->SetUniform("uMaterial.diffuse", 0);
		objectSpecular->Bind();
		objectShader->SetUniform("uMaterial.specular", 1);
		objectShader->SetUniform("uMaterial.shininess", shininess);
		// Directional light uniform
		objectShader->SetUniform("uDirectionalLight.ambient", directionalLight.ambientAmt * directionalLight.diffuse);
		objectShader->SetUniform("uDirectionalLight.diffuse", directionalLight.diffuse);
		objectShader->SetUniform("uDirectionalLight.specular", directionalLight.specularAmt * directionalLight.diffuse);
		objectShader->SetUniform("uDirectionalLight.direction", directionalLight.direction);
		// Spot light uniform
		objectShader->SetUniform("uSpotLight.ambient", spotLight.ambientAmt * spotLight.diffuse);
		objectShader->SetUniform("uSpotLight.diffuse", spotLight.diffuse);
		objectShader->SetUniform("uSpotLight.specular", spotLight.specularAmt * spotLight.diffuse);
		objectShader->SetUniform("uSpotLight.position", camera.GetPosition());
		objectShader->SetUniform("uSpotLight.direction", camera.GetFront());
		objectShader->SetUniform("uSpotLight.constant", 1.0f);
		objectShader->SetUniform("uSpotLight.linear", spotLight.linear);
		objectShader->SetUniform("uSpotLight.quadratic", spotLight.quadratic);
		objectShader->SetUniform("uSpotLight.innerCutoff", glm::cos(glm::radians(spotLight.innerAngle)));
		objectShader->SetUniform("uSpotLight.outerCutoff", glm::cos(glm::radians(spotLight.outerAngle)));
		// Point light uniforms
		for (int i = 0; i < 4; i++)
		{
			std::string lightName = "uPointLight[";
			lightName += std::to_string(i);
			lightName += "]";
			objectShader->SetUniform(lightName + ".ambient", pointLights[i].ambientAmt * pointLights[i].diffuse);
			objectShader->SetUniform(lightName + ".diffuse", pointLights[i].diffuse);
			objectShader->SetUniform(lightName + ".specular", pointLights[i].specularAmt * pointLights[i].diffuse);
			objectShader->SetUniform(lightName + ".position", pointLights[i].position);
			objectShader->SetUniform(lightName + ".constant", 1.0f);
			objectShader->SetUniform(lightName + ".linear", pointLights[i].linear);
			objectShader->SetUniform(lightName + ".quadratic", pointLights[i].quadratic);
		}
		objectShader->SetUniform("uViewPos", camera.GetPosition());
		// Drawing all the cubes in the scene
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objectShader->SetUniform("uModel", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		lightShader->Bind();
		lightShader->SetUniform("uProjection", projection);
		lightShader->SetUniform("uView", view);
		// Drawing all the point lights in the scene
		for (int i = 0; i < 4; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), pointLights[i].position);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader->SetUniform("uModel", model);
			lightShader->SetUniform("uColor", pointLights[i].diffuse);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	void OnRenderImGui() override
	{
		ImGui::Begin("Edit Window");
		ImGui::ColorEdit3("Background Color", &clearColor[0]);
		ImGui::End();
		
		ImGui::Begin("Directional Light");
		ImGui::ColorEdit3("Light Diffuse Color", &directionalLight.diffuse[0]);
		ImGui::SliderFloat("Ambient Strength", &directionalLight.ambientAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strength", &directionalLight.specularAmt, 0.0f, 1.0f);
		ImGui::End();

		// Don't understand how to use Dear ImGui yet so this is my solution
		ImGui::Begin("Point Lights 1");
		ImGui::ColorEdit3("Light Diffuse Color", &pointLights[0].diffuse[0]);
		ImGui::SliderFloat("Ambient Strenght", &(pointLights[0].ambientAmt), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenght", &(pointLights[0].specularAmt), 0.0f, 1.0f);
		ImGui::InputFloat("Linear", &(pointLights[0].linear));
		ImGui::InputFloat("Quadratic", &(pointLights[0].quadratic));
		ImGui::End();

		ImGui::Begin("Point Lights 2");
		ImGui::ColorEdit3("Light Diffuse Color", &pointLights[1].diffuse[0]);
		ImGui::SliderFloat("Ambient Strenght", &(pointLights[1].ambientAmt), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenght", &(pointLights[1].specularAmt), 0.0f, 1.0f);
		ImGui::InputFloat("Linear", &(pointLights[1].linear));
		ImGui::InputFloat("Quadratic", &(pointLights[1].quadratic));
		ImGui::End();

		ImGui::Begin("Point Lights 3");
		ImGui::ColorEdit3("Light Diffuse Color", &pointLights[2].diffuse[0]);
		ImGui::SliderFloat("Ambient Strenght", &(pointLights[2].ambientAmt), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenght", &(pointLights[2].specularAmt), 0.0f, 1.0f);
		ImGui::InputFloat("Linear", &(pointLights[2].linear));
		ImGui::InputFloat("Quadratic", &(pointLights[2].quadratic));
		ImGui::End();

		ImGui::Begin("Point Lights 4");
		ImGui::ColorEdit3("Light Diffuse Color", &pointLights[3].diffuse[0]);
		ImGui::SliderFloat("Ambient Strenght", &(pointLights[3].ambientAmt), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenght", &(pointLights[3].specularAmt), 0.0f, 1.0f);
		ImGui::InputFloat("Linear", &(pointLights[3].linear));
		ImGui::InputFloat("Quadratic", &(pointLights[3].quadratic));
		ImGui::End();

		ImGui::Begin("Spot Light");
		ImGui::ColorEdit3("Light Diffuse Color", &spotLight.diffuse[0]);
		ImGui::SliderFloat("Ambient Strength", &spotLight.ambientAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strength", &spotLight.specularAmt, 0.0f, 1.0f);
		ImGui::SliderFloat("Inner Angle", &spotLight.innerAngle, 0.0f, 90.0f);
		ImGui::SliderFloat("Outer Angle", &spotLight.outerAngle, spotLight.innerAngle, 90.0f);
		ImGui::End();
	}
private:
	const glm::vec3 cubePositions[10] = {
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
	glm::vec3 clearColor = glm::vec3(0.1f);
	VertexArray* vao = nullptr;
	VertexBuffer* vbo = nullptr;
	Shader* lightShader = nullptr;
	Shader* objectShader = nullptr;
	Texture* objectDiffuse = nullptr;
	Texture* objectSpecular = nullptr;
	float shininess = 32.0f;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	struct DirectionalLight
	{
		float ambientAmt = 0.1f;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float specularAmt = 0.5f;

		glm::vec3 direction;
	} directionalLight;
	struct PointLight
	{
		float ambientAmt = 0.1f;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float specularAmt = 0.5f;

		glm::vec3 position;
		float linear = 0.7f;
		float quadratic = 1.4f;
	} pointLights[4];
	struct SpotLight
	{
		float ambientAmt = 0.1f;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float specularAmt = 0.5f;
		
		// Position and direction can be attened from the camera

		float linear = 0.07f;
		float quadratic = 0.017f;

		float innerAngle = 25.0f;
		float outerAngle = 35.0f;
	} spotLight;
};

#endif
