//
// Created by adun on 2017. 11. 20..
//

#include "texture.h"

namespace AdunGL
{
    namespace graphics
    {
        Texture::Texture(const std::string name, const std::string fileName)
        : m_name(name), m_fileName(fileName)
        {
            m_TID = load();
        }

        Texture::~Texture()
        {

        }

        GLuint Texture::load()
        {
            BYTE* pixels = utils::load_image(m_fileName.c_str(), &m_width, &m_height, &m_bits);

            GLuint result;

            glGenTextures(1, &result);

            glBindTexture(GL_TEXTURE_2D, result);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


            if(m_bits != 24 && m_bits !=32)
                ADUNGL_ERROR("[texture.cpp 37] Unsupported image bit-depth! (%d)", m_bits);

            GLint  internalFormat = m_bits == 32 ? GL_RGBA : GL_RGB;
            GLenum format         = m_bits == 32 ? GL_BGRA : GL_BGR;

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);

            glBindTexture(GL_TEXTURE_2D, 0);

            delete[] pixels;

            return result;
        }

        void Texture::bind() const
        {
            glBindTexture(GL_TEXTURE_2D, m_TID);
        }

        void Texture::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}