//
// Created by adun on 2017. 11. 5..
//

#ifndef ADUNGL_INDEXBUFFER_H
#define ADUNGL_INDEXBUFFER_H

#include <GL/glut.h>

namespace AdunGL
{
    namespace graphics
    {
        class IndexBuffer
        {
        private:
            GLuint bufferID;
            GLuint count;

        public:
            IndexBuffer(GLushort* data, GLsizei count);
            ~IndexBuffer();

            void bind() const;
            void unbind() const;

            inline GLuint getCount() const { return count; }
        };
    }
}

#endif //ADUNGL_INDEXBUFFER_H
