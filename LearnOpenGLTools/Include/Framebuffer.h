#pragma once
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GPUBuffer.h>
#include <Texture.h>

class Framebuffer : public GPUBuffer
{
public:
	Framebuffer();
	Framebuffer(unsigned int width, unsigned int height);
	~Framebuffer();
	void Bind() const override;
	void Unbind() const override;
	void PrepDraw() const;
private:
	unsigned int m_Texture;
	unsigned int m_Renderbuffer;
};

#endif