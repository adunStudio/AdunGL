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
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            //glGenBuffers(1, &vbo);
            //glBindBuffer(GL_ARRAY_BUFFER, vbo);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);
        }

        void IndexBuffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        }

        void IndexBuffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}