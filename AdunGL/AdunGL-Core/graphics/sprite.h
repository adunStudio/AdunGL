#pragma once

//
// Created by adun on 2017. 11. 18..
//

#include "./bases/renderable2d.h"

namespace AdunGL
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			maths::vec3& position;
			maths::vec2& size;

		public:
			Sprite(float x, float y, float width, float height, const maths::vec4& color);

			Sprite(float x, float y, float width, float height, Texture* texture);

			Sprite(Texture* texture);

			Sprite(float x, float y, Texture* texture);

			void setUV(std::vector<maths::vec2> uv);
		};
	}
}
