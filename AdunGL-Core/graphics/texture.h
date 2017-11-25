//
// Created by adun on 2017. 11. 20..
//

#ifndef ADUNGL_TEXTURE_H
#define ADUNGL_TEXTURE_H

#include <FreeImage.h>
#include <string>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include "../utils/imageload.h"

namespace AdunGL
{
    namespace graphics
    {
        class Texture
        {
        private:
            std::string m_fileName;
            GLuint m_TID;
            GLsizei m_width, m_height;

        public:
            Texture(const std::string fileName);
            ~Texture();

            void bind()   const;
            void unbind() const;

            inline const unsigned int getWidth () const { return m_width;  }
            inline const unsigned int getHeight() const { return m_height; }
            inline const unsigned int getID    () const { return m_TID; }

        private:
            GLuint load();
        };
    }
}
#endif //ADUNGL_TEXTURE_H
