#include <Texture.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const char* texturePath, unsigned int slot, bool pixelated)
	: m_Slot(slot)
{
	int bpc;
	unsigned char* data = stbi_load(texturePath, (int*)&m_Width, (int*)&m_Height, &bpc, 0);
	if (!data)
	{
		std::cout << "\033[41m\033[30mERROR::Texture\033[0m " << stbi_failure_reason() << std::endl;
		stbi_image_free(data);
		return;
	}
	glGenTextures(1, &m_BufferID);
	glBindTexture(GL_TEXTURE_2D, m_BufferID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0,
		bpc == 1 ? GL_RED : bpc == 2 ? GL_RG : bpc == 4 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int slot, bool pixelated)
	:m_Width{ width }, m_Height{ height }
{
	glGenTextures(1, &m_BufferID);
	glBindTexture(GL_TEXTURE_2D, m_BufferID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_BufferID);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_Slot);
	glBindTexture(GL_TEXTURE_2D, m_BufferID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
