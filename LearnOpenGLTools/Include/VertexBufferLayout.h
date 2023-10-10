#pragma once
#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <glad/glad.h>
#include <cassert>

struct VertexBufferLayout
{
public:
	VertexBufferLayout() = default;
	/**
	 * @brief Pushes a new element to the standard vector of elements to be enabled, while also 
	 * increasing the stride count
	 * 
	 * @param[in] count The number of elements that make up the vertex attribute
	 */
	template<typename T>
	VertexBufferLayout& Push(unsigned int count)
	{
		assert(false && "Data type trying to be pushed isn't supported!");
		return *this;
	}
	template<>
	VertexBufferLayout& Push<float>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT });
		m_Stride += count * sizeof(float);
		return *this;
	}
	/**
	 * @brief Enables all the vertex attributes that have been pushed
	 */
	void Enable() const
	{
		int index = 0;
		int offset = 0;
		for (const auto& elem : m_Elements)
		{
			glVertexAttribPointer(index, elem.count, elem.type, GL_FALSE, m_Stride, reinterpret_cast<void*>(offset));
			glEnableVertexAttribArray(index++);
			offset += elem.count * sizeof(float);
		}
	}
private:
	struct Element
	{
		unsigned int count;
		unsigned int type;
	};
	std::vector<Element> m_Elements;
	unsigned int m_Stride{ 0 };
};

#endif