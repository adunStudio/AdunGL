//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_SPRITE_H
#define ADUNGL_SPRITE_H

#include "renderable2d.h"

namespace AdunGL
{
    namespace graphics
    {
        class Sprite : public Renderable2D
        {
        public:
            maths::vec3& position;

        public:
            Sprite(float x, float y , float width, float height, const maths::vec4& color);

            Sprite(float x, float y , float width, float height, Texture* texture);
        };
    }
}
#endif //ADUNGL_SPRITE_H
