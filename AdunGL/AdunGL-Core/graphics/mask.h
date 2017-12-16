#pragma once

//
// Created by adun on 2017. 11. 29..
//


#include "texture.h"
#include "../maths/maths.h"

namespace AdunGL
{
	namespace graphics
	{
		struct Mask
		{
			Texture* texture;
			maths::mat4 transform;

			Mask(Texture* texture, const maths::mat4& transform = maths::mat4::Identity())
				:texture(texture), transform(transform)
			{
				this->transform = maths::mat4::Scale(maths::vec3((float)texture->getWidth() / (float)texture->getHeight(), 1.0f, 1.0f));
			}
		};
	}
}
