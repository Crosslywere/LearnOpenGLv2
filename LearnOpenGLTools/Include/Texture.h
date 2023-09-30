#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GPUBuffer.h>

class Texture : GPUBuffer
{
public:
	Texture() = default;
	Texture(const char* texturePath, unsigned int slot = 0, bool pixelated = false);
	Texture(unsigned int width, unsigned int height, unsigned int slot = 0 , bool pixelated = false);
	~Texture() override;
	void Bind() const override;
	void Unbind() const override;
	inline const unsigned int& GetWidth() const { return m_Width; }
	inline const unsigned int& GetHeight() const { return m_Height; }
	inline void SetSlot(unsigned int slot) { m_Slot = slot; }
	inline const int& GetSlot() const { return m_Slot; }
private:
	unsigned int m_Slot{ 0 };
	unsigned int m_Width, m_Height;
};

#endif