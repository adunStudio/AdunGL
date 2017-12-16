#pragma once

#include <GL/freeglut.h>

namespace AdunGL
{
	namespace graphics
	{
		namespace API
		{
			inline GLuint CreateVertexArray()
			{
				GLuint result;
				glGenVertexArrays(1, &result);
				
				return result;
			}

			inline GLuint CreateBuffer()
			{
				GLuint result;
				glGenBuffers(1, &result);

				return result;
			}

			inline GLuint CreateFrameBuffer()
			{
				GLuint result;
				glGenFramebuffers(1, &result);

				return result;
			}

			inline GLuint CreateRenderBuffer()
			{
				GLuint result;
				glGenRenderbuffers(1, &result);

				return result;
			}

			inline void CreateVertexArrays(GLuint size, GLuint* arrays)
			{
				glGenVertexArrays(size, arrays);
			}

			inline void CreateVertexBuffers(GLuint size, GLuint* buffers)
			{
				glGenVertexArrays(size, buffers);
			}

			inline void CreateFramebuffers(GLuint size, GLuint* buffers)
			{
				glGenFramebuffers(size, buffers);
			}

			inline void CreateRenderbuffers(GLuint size, GLuint* buffers)
			{
				glGenRenderbuffers(size, buffers);
			}

			inline void BindVertexArray(GLuint array)
			{
				glBindVertexArray(array);
			}

			inline void BindBuffer(GLuint target, GLuint buffer)
			{
				glBindBuffer(target, buffer);
			}

			inline void BindFramebuffer(GLuint target, GLuint buffer)
			{
				glBindFramebuffer(target, buffer);
			}

			inline void BindRenderbuffer(GLuint target, GLuint buffer)
			{
				glBindRenderbuffer(target, buffer);
			}

			inline int GetScreenBuffer()
			{
				int result;
				glGetIntegerv(GL_FRAMEBUFFER_BINDING, &result);
				return result;
			}

			inline void SetBufferData(GLuint target, GLuint size, const void* data, GLuint usage)
			{
				glBufferData(target, size, data, usage);
			}

			inline void SetBufferSubData(GLuint target, ptrdiff_t offset, ptrdiff_t size, const void* data)
			{
				glBufferSubData(target, offset, size, data);
			}

			inline void* GetBufferPointer(GLuint target, GLuint access)
			{
				void* result = glMapBuffer(target, access);
				return result;
			}

			inline void ReleaseBufferPointer(GLuint target)
			{
				glUnmapBuffer(target);
			}

			inline void FramebufferTexture2D(GLuint target, GLuint attachment, GLuint textarget, GLuint texture, int level)
			{
				glFramebufferTexture2D(target, attachment, textarget, texture, level);
			}

			inline void FramebufferRenderbuffer(GLuint target, GLuint attachment, GLuint renderbuffertarget, GLuint renderbuffer)
			{
				glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
			}

			inline void RenderbufferStorage(GLuint target, GLuint format, GLuint width, GLuint height)
			{
				glRenderbufferStorage(target, format, width, height);
			}

			inline void SetViewport(GLuint x, GLuint y, GLuint width, GLuint height)
			{
				glViewport(x, y, width, height);
			}

			inline void Clear(GLuint flags)
			{
				glClear(flags);
			}

			inline void SetClearColor(float r, float g, float b, float a)
			{
				glClearColor(r, g, b, a);
			}

			inline GLuint CreateTexture()
			{
				GLuint result;
				glGenTextures(1, &result);
				return result;
			}

			inline void CreateTextures(GLuint size, GLuint* textures)
			{
				glGenTextures(size, textures);
			}

			inline void BindTexture(GLuint target, GLuint texture)
			{
				glBindTexture(target, texture);
			}

			inline void UnbindTexture(GLuint target)
			{
				glBindTexture(target, 0);
			}

			inline void SetTextureParameter(GLuint target, GLuint parameter, int value)
			{
				glTexParameteri(target, parameter, value);
			}

			inline void SetTextureData(GLuint target, GLuint internalformat, GLuint width, GLuint height, GLuint format, GLuint type, const void* pixels)
			{
				glTexImage2D(target, 0, internalformat, width, height, 0, format, type, pixels);
			}

			inline void SetActiveTexture(GLuint texture)
			{
				glActiveTexture(texture);
			}

			inline void UnbindVertexArrays()
			{
				glBindVertexArray(0);
			}

			inline void UnbindBuffers(GLuint target)
			{
				glBindBuffer(target, 0);
			}

			inline void EnableVertexAttribute(GLuint index)
			{
				glEnableVertexAttribArray(index);
			}

			inline void DisableVertexAttribute(GLuint index)
			{
				glDisableVertexAttribArray(index);
			}

			inline void SetVertexAttributePointer(GLuint index, int size, GLuint type, bool normalized, GLuint stride, GLuint offset)
			{
				glVertexAttribPointer(index, size, type, (GLuint)normalized, stride, (const GLvoid*)offset);
			}

			inline void FreeArray(GLuint array)
			{
				glDeleteVertexArrays(1, &array);
			}

			inline void FreeBuffer(GLuint buffer)
			{
				glDeleteBuffers(1, &buffer);
			}

			inline void FreeFramebuffer(GLuint buffer)
			{
				glDeleteFramebuffers(1, &buffer);
			}

			inline void FreeVertexArray(GLuint array)
			{
				glDeleteVertexArrays(1, &array);
			}

			inline void FreeVertexArrays(GLuint size, GLuint* arrays)
			{
				glDeleteVertexArrays(size, arrays);
			}

			inline void FreeBuffers(GLuint size, GLuint* buffers)
			{
				glDeleteBuffers(size, buffers);
			}

			inline void FreeFramebuffers(GLuint size, GLuint* buffers)
			{
				glDeleteFramebuffers(size, buffers);
			}

			inline void FreeTexture(GLuint texture)
			{
				glDeleteTextures(1, &texture);
			}

			inline void FreeTextures(GLuint size, GLuint* textures)
			{
				glDeleteTextures(size, textures);
			}

			inline void DrawElements(GLuint mode, GLuint count, GLuint type, const void* indices)
			{
				glDrawElements(mode, count, type, indices);
			}

		}
	}
}