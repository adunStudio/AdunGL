//
// Created by adun on 2017. 11. 29..
//

#ifndef ADUNGL_TEXTURE_MANAGER_H
#define ADUNGL_TEXTURE_MANAGER_H

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
            TextureManager() { };  // 생성자 X

        };
    }
}
#endif //ADUNGL_TEXTURE_MANAGER_H
