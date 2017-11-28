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
        : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color), position(m_position), size(m_size)
        {

        }

        Sprite::Sprite(float x, float y , float width, float height, Texture* texture)
        : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), maths::vec4(1, 1 , 1, 1)), position(m_position), size(m_size)
        {
            m_texture = texture;
        }

        Sprite::Sprite(Texture* texture)
        : Renderable2D(maths::vec3(0, 0, 0), maths::vec2(texture->getWidth(), texture->getHeight()), maths::vec4(1, 1 , 1, 1)), position(m_position), size(m_size)
        {
            m_texture = texture;
        }

        Sprite::Sprite(float x, float y, Texture* texture)
        : Renderable2D(maths::vec3(x, y, 0), maths::vec2(texture->getWidth(), texture->getHeight()), maths::vec4(1, 1 , 1, 1)), position(m_position), size(m_size)
        {
            m_texture = texture;
        }

        void Sprite::setUV(std::vector<maths::vec2> uv)
        {
            m_uv = uv;
        }
    }
}