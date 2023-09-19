#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GPUBuffer.h>

/**
 * @brief A vertex array buffer that associates with the current array on the GPU to be drawn
 */
class VertexArray : public GPUBuffer
{
public:
	VertexArray();
	~VertexArray() override;
	void Bind() const override;
	void Unbind() const override;
};

#endif // VERTEX_ARRAY_H