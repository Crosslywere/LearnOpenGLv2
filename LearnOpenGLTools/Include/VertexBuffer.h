#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GPUBuffer.h>

class VertexBuffer : public GPUBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(void* data, unsigned int size);
	~VertexBuffer() override;
	void Bind() const override;
	void Unbind() const override;
};

#endif // VERTEX_BUFFER_H