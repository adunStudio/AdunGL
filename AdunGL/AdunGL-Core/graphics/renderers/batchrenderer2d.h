#pragma once

//
// Created by adun on 2017. 11. 18..
//


#include <cstddef>
#include <GL/freeglut.h>
#include <GL/glew.h>
#include "../bases/renderer2d.h"
#include "../bases/renderable2d.h"

namespace AdunGL
{
#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData) // renderable.c ±¸Á¶Ã¼
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES   32

#define SHADER_VERTEX_INDEX   0
#define SHADER_UV_INDEX       1
#define SHADER_MASK_UV_INDEX  2
#define SHADER_TID_INDEX      3
#define SHADER_MID_INDEX      4
#define SHADER_COLOR_INDEX    5

	namespace graphics {
		class BatchRenderer2D : public Renderer2D {

		private:
			GLuint m_vao;
			GLuint m_vbo;
			IndexBuffer* m_ibo;
			GLsizei m_indexCount = 0;
			VertexData* m_buffer;

			std::vector<GLuint> m_textureSlots;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D *renderable) override;
			void drawString(const std::string& text, const maths::vec3& position, const Font& font, const maths::vec4& color) override;
			void end() override;
			void flush() override;

		private:
			void init();
			float submitTexture(GLuint textureID);
			float submitTexture(const Texture* texture);
		};
	}
}