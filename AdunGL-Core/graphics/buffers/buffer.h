//
// Created by adun on 2017. 11. 5..
//

#ifndef ADUNGL_BUFFER_H
#define ADUNGL_BUFFER_H

#include <GL/glut.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

namespace AdunGL
{
    namespace graphics
    {
        class Buffer
        {
        private:
            GLuint bufferID;
            GLuint componentCount;

        public:
            Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
            ~Buffer();

            void bind() const;
            void unbind() const;

            inline GLuint getComponentCount() const { return componentCount; }
        };
    }
}

#endif //ADUNGL_BUFFER_H
