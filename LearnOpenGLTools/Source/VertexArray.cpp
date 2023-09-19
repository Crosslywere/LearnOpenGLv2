#include <VertexArray.h>
#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_BufferID);
	glBindVertexArray(m_BufferID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_BufferID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_BufferID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}