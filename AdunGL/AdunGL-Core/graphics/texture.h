#pragma once

//
// Created by adun on 2017. 11. 20..
//


#include <FreeImage.h>
#include <string>
#include <GL\freeglut.h>
#include "../utils/imageload.h"
#include "../utils/log.h"

namespace AdunGL
{
	namespace graphics
	{

		enum class TextureWrap
		{
			REPEAT          = GL_REPEAT,
			CLAMP           = GL_CLAMP,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE   = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		enum class TextureFilter
		{
			LINEAR = GL_LINEAR,
			NEARST = GL_NEAREST
		};

		class Texture
		{
		private:
			static TextureWrap   s_wrapMode;
			static TextureFilter s_filterMode;

		private:
			std::string m_name;
			std::string m_fileName;
			GLuint m_TID;
			GLuint m_width, m_height;
			unsigned m_bits;

		public:
			Texture(GLuint width, GLuint height, GLuint bits = 24);
			Texture(const std::string name, const std::string fileName);
			~Texture();

			void bind()   const;
			void unbind() const;

			inline const std::string& getName() const { return m_name; }
			inline const unsigned int getWidth() const { return m_width; }
			inline const unsigned int getHeight() const { return m_height; }
			inline const unsigned int getID() const { return m_TID; }

		public:
			inline static void SetWrap  (TextureWrap mode)   { s_wrapMode   = mode; }
			inline static void setFIlter(TextureFilter mode) { s_filterMode = mode; }

		private:
			GLuint load();
		};
	}
}
