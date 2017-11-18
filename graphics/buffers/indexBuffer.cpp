//
// Created by adun on 2017. 11. 5..
//

#include "indexBuffer.h"

namespace AdunGL
{
    namespace graphics
    {
        IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
        :count(count)
        {
            glGenBuffers(1, &bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind
        }

        IndexBuffer::~IndexBuffer()
        {
            glDeleteBuffers(1, &bufferID);
        }

        void IndexBuffer::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
        }

        void IndexBuffer::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}