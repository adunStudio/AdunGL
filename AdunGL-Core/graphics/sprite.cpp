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
       : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color)
       {

       }
    }
}