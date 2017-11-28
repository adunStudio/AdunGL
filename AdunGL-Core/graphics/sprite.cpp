//
// Created by adun on 2017. 11. 18..
//

#include "sprite.h"
#include "renderable2d.h"

namespace AdunGL
{
    namespace graphics
    {
        Sprite::Sprite(float x, float y, float width, float height, const maths::vec4 &color)
        : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color), position(m_position)
        {

        }

        Sprite::Sprite(float x, float y , float width, float height, Texture* texture)
        : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), maths::vec4(1, 1 , 1, 1)), position(m_position)
        {
            m_texture = texture;
        }
    }
}