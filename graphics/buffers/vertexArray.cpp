//
// Created by adun on 2017. 11. 5..
//

#include "vertexArray.h"

namespace AdunGL
{
    namespace graphics
    {
        VertexArray::VertexArray()
        {
            // TODO: need Window Version
            glGenVertexArraysAPPLE(1, &arrayID);
        }

        VertexArray::~VertexArray()
        {
            for(int i = 0; i < buffers.size(); ++i)
                delete buffers[i];
        }

        void VertexArray::addBuffer(Buffer *buffer, GLuint index)
        {
            // index -> shader_index

            bind();
            buffer->bind();

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();
        }

        void VertexArray::bind() const
        {
            glBindVertexArrayAPPLE(arrayID);
        }

        void VertexArray::unbind() const
        {
            glBindVertexArrayAPPLE(0);
        }
    }
}