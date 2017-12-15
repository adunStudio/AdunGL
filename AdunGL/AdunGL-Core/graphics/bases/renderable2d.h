#pragma once

//
// Created by adun on 2017. 11. 18..
//

#include <vector>
#include "../buffers/buffer.h"
#include "../buffers/indexBuffer.h"
#include "../buffers/vertexArray.h"
#include "../shaders/shader.h"
#include "../../maths/maths.h"
#include "renderer2d.h"
#include "../texture.h"


namespace AdunGL
{
	namespace graphics
	{

		struct VertexData
		{
			maths::vec3  vertex;
			maths::vec2  uv;
			maths::vec2  mask_uv;
			float        tid;
			float        mid;
			unsigned int color;
		};

#define RENDERER_VERTEX_SIZE    sizeof(AdunGL::graphics::VertexData) // renderable.c 구조체

		class Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;
			maths::vec4 m_color;
			std::vector<maths::vec2> m_uv;
			Texture*    m_texture;

		protected:
			Renderable2D() : m_texture(nullptr) { setUVDefaults(); };

		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
				: m_position(position), m_size(size), m_color(color), m_texture(nullptr) {
				setUVDefaults();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

		public:
			inline const maths::vec3&              getPosition() const { return m_position; }
			inline const maths::vec2&              getSize()     const { return m_size; }
			inline const maths::vec4&              getColor()    const { return m_color; }
			inline const std::vector<maths::vec2>& getUV()       const { return m_uv; }
			inline const GLuint                    getTID()      const { return m_texture ? m_texture->getID() : 0; }
			inline const Texture*                  getTexture()  const { return m_texture; }

		private:
			void setUVDefaults()
			{
				// 시계방향
				m_uv.push_back(maths::vec2(0, 0));
				m_uv.push_back(maths::vec2(0, 1));
				m_uv.push_back(maths::vec2(1, 1));
				m_uv.push_back(maths::vec2(1, 0));
			}
		};
	}
}
