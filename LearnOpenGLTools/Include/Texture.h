#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GPUBuffer.h>

class Texture : GPUBuffer
{
public:
	Texture() = default;
	Texture(const char* texturePath, bool pixelated = false);
	~Texture() override;
	void Bind() const override;
	void Unbind() const override;
	inline const unsigned int& GetWidth() const { return m_Width; }
	inline const unsigned int& GetHeight() const { return m_Height; }
	inline void SetSlot(unsigned int slot) { m_Slot = slot; }
private:
	unsigned int m_Slot{ 0 };
	unsigned int m_Width, m_Height;
};

#endif