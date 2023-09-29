#pragma once
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <GPUBuffer.h>
#include <glad/glad.h>
#include <iostream>

class FrameBuffer : public GPUBuffer
{
public:
	inline FrameBuffer() = default;
	inline FrameBuffer(unsigned int width, unsigned int height)
	{
		glGenFramebuffers(1, &m_BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
		// The texture to write data into
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		CheckFrameBufferStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	inline ~FrameBuffer()
	{
		glDeleteTextures(1, &colorTexture);
		glDeleteRenderbuffers(1, &rbo);
		glDeleteFramebuffers(1, &m_BufferID);
	}
	inline void Bind() const override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
	}
	inline void Unbind() const override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	unsigned int colorTexture;
private:
	unsigned int rbo;
	void CheckFrameBufferStatus() const
	{
		unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "\033[41m\033[30mERROR::Framebuffer\033[0m ";
			switch (status)
			{
			case GL_FRAMEBUFFER_UNDEFINED:
				std::cout << "Frame buffer undefined!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				std::cout << "Incomplete framebuffer attachment!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				std::cout << "Incomplete/missing framebuffer attachment!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				std::cout << "Incomplete draw buffer for framebuffer!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				std::cout << "Incomplete read buffer for framebuffer!" << std::endl;
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				std::cout << "Unsupported framebuffer!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				std::cout << "Incomplete layer targets!" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				std::cout << "Incomplete multi sample in framebuffer!" << std::endl;
				break;
			default:
				std::cout << "Unidentified error!!" << std::endl;
			}
		}
	}
};

#include <Window.h>
#include <Camera.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Texture.h>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp>

class FrameBufferTest : public Application
{
public:
	FrameBufferTest()
	{
		fbo = new FrameBuffer(Window::GetWidth(), Window::GetHeight());
		float screenQuadVertices[24] = {
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f,

			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
		};
		screenQuadVAO = new VertexArray();
		screenQuadVAO->Bind();
		screenQuadVBO = new VertexBuffer(screenQuadVertices, sizeof(screenQuadVertices));
		screenQuadVBO->Bind();
		VertexBufferLayout().Push<float>(2).Push<float>(2).Enable();
		screenQuadVAO->Unbind();
		screenQuadVBO->Unbind();
		framebufferShader = new Shader("Resource/Shader/Framebuffer/framebuffer_shader.vert", "Resource/Shader/Framebuffer/framebuffer_shader.frag");
		float cubeVertices[] = {
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
		cubeVAO = new VertexArray();
		cubeVAO->Bind();
		cubeVBO = new VertexBuffer(cubeVertices, sizeof(cubeVertices));
		cubeVBO->Bind();
		VertexBufferLayout().Push<float>(3).Push<float>(2).Enable();
		cubeVAO->Unbind();
		cubeVBO->Unbind();
		cubeShader = new Shader("Resource/Shader/TexturedCube/cube_shader.vert", "Resource/Shader/TexturedCube/cube_shader.frag");
		cubeTexture = new Texture("Resource/Texture/container.jpg");
	}
	~FrameBufferTest()
	{
		delete fbo;
		delete cubeVAO;
		delete cubeVBO;
		delete screenQuadVAO;
		delete screenQuadVBO;
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
	void OnRender()
	{
		glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), Window::GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		fbo->Bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		cubeVAO->Bind();
		cubeShader->Bind();
		cubeShader->SetUniform("uMVP", projection * view * model);
		cubeShader->SetUniform("uTexture2D", cubeTexture->GetSlot());
		cubeTexture->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		fbo->Unbind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		framebufferShader->Bind();
		screenQuadVAO->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbo->colorTexture);
		framebufferShader->SetUniform("screenTexture", 0);
		glDisable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
private:
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	FrameBuffer* fbo = nullptr;
	VertexArray* cubeVAO = nullptr;
	VertexArray* screenQuadVAO = nullptr;
	VertexBuffer* cubeVBO = nullptr;
	VertexBuffer* screenQuadVBO = nullptr;
	Shader* framebufferShader = nullptr;
	Shader* cubeShader = nullptr;
	Texture* cubeTexture = nullptr;
};

#endif