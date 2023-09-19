#pragma once
#ifndef GPU_BUFFER_H
#define GPU_BUFFER_H

/**
 * @brief An abstract buffer of memory allocated on the GPU.
 * Can be implemented by VertexBuffers, IndexBuffers, etc.
 */
class GPUBuffer
{
public:
	GPUBuffer() = default;
	virtual ~GPUBuffer() {}
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
protected:
	unsigned int m_BufferID{ 0 };
};

#endif // GPU_BUFFER_H