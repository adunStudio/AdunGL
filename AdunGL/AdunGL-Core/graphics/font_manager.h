#pragma once
//
// Created by adun on 2017. 11. 27..
//


#include <vector>
#include "font.h"

namespace AdunGL
{
	namespace graphics
	{
		class FontManager
		{
		private:
			static std::vector<Font*> m_fonts;

		public:
			static void add(Font* font);

			static Font* get();
			static Font* get(const std::string& name);
			static Font* get(const std::string& name, unsigned int size);

			static void clean();

		private:
			FontManager() = delete;  // default 생성자 X => 인스턴스 X
		};
	}
}