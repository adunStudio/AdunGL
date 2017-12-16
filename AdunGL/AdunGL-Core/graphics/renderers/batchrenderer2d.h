#pragma once

//
// Created by adun on 2017. 11. 18..
//


#include <cstddef>
#include <GL/freeglut.h>
#include <GL/glew.h>
#include "../bases/renderer2d.h"
#include "../bases/renderable2d.h"
#include "../buffers/framebuffer.h"
#include "../shaders/shader_factory.h"
#include "../mesh_factory.h"
#include "../buffers/vertexArray.h"
#include "../buffers/indexBuffer.h"
#include "../api/render_api.h"

namespace AdunGL
{
#define RENDERER_MAX_SPRITES    60000
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES   32 - 1


	// Á¤¿Õµ¿ 2295-10 501È£  1Ãþ Çö°ü #1212#

	namespace graphics {

		class BatchRenderer2D : public Renderer2D {

		private:
			VertexArray* m_vertexArray;
			GLuint m_vao;
			GLuint m_vbo;
			IndexBuffer* m_ibo;
			IndexBuffer* m_lineIbo;
			GLsizei m_indexCount, m_lineIndexCount;
			VertexData* m_buffer;


			std::vector<GLuint> m_textureSlots;

			FrameBuffer* m_frameBuffer;
			FrameBuffer* m_postEffectsBuffer;

			int          m_screenBuffer;

			maths::tvec2<GLuint> m_viewportSize, m_screenSize;

			Shader* m_simpleShader;

			VertexArray* m_screenQuad;

		public:
			BatchRenderer2D(GLuint width, GLuint height);
			BatchRenderer2D(const maths::tvec2<GLuint>& screenSize);
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D *renderable) override;
			void drawAABB(const maths::AABB& aabb, maths::vec4 color = maths::vec4(1, 0, 0, 0));
			void drawString(const std::string& text, const maths::vec3& position, const Font& font, const maths::vec4& color) override;
			void end() override;
			void flush() override;

		public:
			inline       void                  setScreenSize(const maths::tvec2<GLuint>& size)       { m_screenSize = size; }
			inline const maths::tvec2<GLuint>& getScreenSize()                                 const { return m_screenSize; }

			inline       void                  setViewportSize(const maths::tvec2<GLuint>& size)     { m_viewportSize = size; }
			inline const maths::tvec2<GLuint>& getViewportSize()                               const { return m_viewportSize; }

		private:
			void init();
			float submitTexture(GLuint textureID);
			float submitTexture(const Texture* texture);
		};
	}
}