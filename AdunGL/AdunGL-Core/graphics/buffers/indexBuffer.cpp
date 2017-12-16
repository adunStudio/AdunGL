//
// Created by adun on 2017. 11. 5..
//

#include "indexBuffer.h"

namespace AdunGL
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
			: m_count(count)
		{
			m_buffer = new Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_buffer->bind();
			m_buffer->setData(count * sizeof(GLushort), data);
			m_buffer->unbind();
			//glGenBuffers(1, &bufferID);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind
		}

		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
			: m_count(count)
		{
			m_buffer = new Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_buffer->bind();
			m_buffer->setData(count * sizeof(GLuint), data);
			m_buffer->unbind();
			//glGenBuffers(1, &bufferID);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind
		}

		IndexBuffer::~IndexBuffer()
		{
			delete m_buffer;
			//glDeleteBuffers(1, &bufferID);
		}

		void IndexBuffer::bind() const
		{
			m_buffer->bind();
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		}

		void IndexBuffer::unbind() const
		{
			m_buffer->unbind();
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}