//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_MATH_FUNC_H
#define ADUNGL_MATH_FUNC_H
#define _USE_MATH_DEFINES

#include <cmath>

namespace AdunGL
{
    namespace maths
    {
        inline float toRadians(float degrees)
        {
            return degrees * (M_PI / 180.0f);
        }

        const float RADIAN = static_cast<float>(M_PI / 180);

    }
}

#endif //ADUNGL_MATH_FUNC_H
