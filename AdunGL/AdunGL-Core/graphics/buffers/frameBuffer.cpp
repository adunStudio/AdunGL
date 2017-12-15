#include "frameBuffer.h"


// http://blog.daum.net/aero2k/53

namespace AdunGL
{
	namespace graphics
	{
		FrameBuffer::FrameBuffer(const maths::tvec2<GLuint>& size)
			: m_size(size), m_width(m_size.x), m_height(m_size.y), m_clearColor(maths::vec4(0.0f, 0.0f, 0.0f, 0.1f))
		{
			create(m_width, m_height);
		}

		FrameBuffer::FrameBuffer(GLuint width, GLuint height)
			: m_size(width, height), m_width(m_size.x), m_height(m_size.y), m_clearColor(maths::vec4(0.0f, 0.0f, 0.0f, 0.1f))
		{
			create(width, height);
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_data.framebufferID);
		}

		void FrameBuffer::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_data.framebufferID);
			glViewport(0, 0, m_width, m_height);
		}

		void FrameBuffer::clear()
		{
			glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void FrameBuffer::create(GLuint width, GLuint height)
		{
			glGenFramebuffers (1, &m_data.framebufferID);
			glGenRenderbuffers(1, &m_data.depthbufferID);

			Texture::setFIlter(TextureFilter::LINEAR);
			m_texture = new Texture(width, height);

			glBindRenderbuffer(GL_RENDERBUFFER, m_data.depthbufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

			glBindFramebuffer(GL_FRAMEBUFFER, m_data.framebufferID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getID(), 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_data.depthbufferID);
		}
	}
}