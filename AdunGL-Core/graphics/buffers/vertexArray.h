//
// Created by adun on 2017. 11. 5..
//

#ifndef ADUNGL_VERTEXARRAY_H
#define ADUNGL_VERTEXARRAY_H

#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <vector>
#include "buffer.h"

namespace AdunGL
{
    namespace graphics
    {
        class VertexArray
        {
        private:
            GLuint arrayID;
            std::vector<Buffer* > buffers;

        public:
            VertexArray();
            ~VertexArray();

            void addBuffer(Buffer* buffer, GLuint index);

            void bind() const;
            void unbind() const;
        };

    }
}
#endif //ADUNGL_VERTEXARRAY_H
