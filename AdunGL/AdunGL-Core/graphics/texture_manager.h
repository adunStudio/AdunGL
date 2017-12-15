#pragma once

//
// Created by adun on 2017. 11. 29..
//

#include <vector>
#include "texture.h"

namespace AdunGL
{
	namespace graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> m_textures;

		public:
			static void add(Texture* texture);
			static Texture* get(const std::string& name);
			static void clean();

		private:
			TextureManager() { };  // »ý¼ºÀÚ X

		};
	}
}