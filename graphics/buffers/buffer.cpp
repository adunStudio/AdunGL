//
// Created by adun on 2017. 11. 5..
//

#include "buffer.h"

namespace AdunGL
{
    namespace graphics
    {
        Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
        :componentCount(componentCount)
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

        void Buffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        }

        void Buffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}