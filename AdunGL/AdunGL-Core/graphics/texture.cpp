//
// Created by adun on 2017. 11. 20..
//

#include "texture.h"

namespace AdunGL
{
	namespace graphics
	{
		TextureWrap Texture::s_wrapMode = REPEAT;

		Texture::Texture(GLuint width, GLuint height)
			: m_width(width), m_height(height), m_fileName("NULL")
		{
			m_TID = load();
		}

		Texture::Texture(const std::string name, const std::string fileName)
			: m_name(name), m_fileName(fileName)
		{
			m_TID = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_TID);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = nullptr;
			
			if (m_fileName != "NULL")
				pixels = utils::load_image(m_fileName.c_str(), &m_width, &m_height, &m_bits);
			else
				m_bits = 32;


			GLuint result;

			glGenTextures(1, &result);

			glBindTexture(GL_TEXTURE_2D, result);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_wrapMode);


			if (m_bits != 24 && m_bits != 32)
				ADUNGL_ERROR("[texture.cpp 37] Unsupported image bit-depth! (%d)", m_bits);

			GLint  internalFormat = m_bits == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_bits == 32 ? GL_BGRA : GL_BGR;

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL);

			glBindTexture(GL_TEXTURE_2D, 0);

			if(pixels != nullptr)
				delete[] pixels;

			return result;

			/*
			(1) glGenTexture()    Texture ID�� ����
			(2) glBindTexture()   ������ Texture ID�� ���ε�
			(3) glTexImage2D()    RGBA byte array�� ����,
			(4) glTexParameteri() ������� GL_TEXTURE_MIN_FILTER, Ȯ�� ���� GL_TEXTURE_MAG_FILTER�� ����
			(5) glTexParameteri() GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T�� �̿�
			Vertex ������ ��� ������ �ε巴�� ���� �����ִ� GL_CLAMP_TO_EDGE �� �ؽ��ĸ� ��� �ݺ� ��ų GL_REPEAT�� ����
			*/
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