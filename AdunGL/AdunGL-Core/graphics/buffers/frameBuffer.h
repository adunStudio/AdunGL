#pragma once

#include "../../maths/vec4.h"
#include "../../maths/vec2.h"
#include "../../maths/tvec2.h"
#include "../texture.h"

// http://blog.daum.net/aero2k/53

namespace AdunGL
{
	namespace graphics
	{
		class FrameBuffer
		{
		private:
			struct FrameBufferData
			{
				GLuint framebufferID;
				GLuint depthbufferID;
			};

			Texture* m_texture;
			FrameBufferData m_data;

			maths::tvec2<GLuint> m_size;

			GLuint& m_width;
			GLuint& m_height;

			maths::vec4 m_clearColor;

		public:
			FrameBuffer(const maths::tvec2<GLuint>& size);
			FrameBuffer(GLuint width, GLuint height);

			~FrameBuffer();

			void bind() const;

			void clear();

			inline const maths::tvec2<GLuint>& getSIze()    const { return m_size;   }
			inline const GLuint                getWidth()   const { return m_width;  }
			inline const GLuint                getHeight()  const { return m_height; }
			inline const Texture*              getTexture() const { return m_texture;}

			inline void setClearColor(const maths::vec4& color) { m_clearColor = color;  }

		private:
			void create(GLuint width, GLuint height);
		};
	}
}