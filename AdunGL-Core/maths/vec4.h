//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_vec4_H
#define ADUNGL_vec4_H

#include <iostream>

namespace AdunGL
{
    namespace maths
    {
        struct vec4
        {
            float x, y, z, w;

            vec4() = default;
            vec4(const float& x, const float& y, const float& z, const float& w);

            vec4& add(const vec4& other);
            vec4& subtract(const vec4& other);
            vec4& multiply(const vec4& other);
            vec4& divide(const vec4& other);

            friend vec4& operator+(vec4& left, const vec4& right);
            friend vec4& operator-(vec4& left, const vec4& right);
            friend vec4& operator*(vec4& left, const vec4& right);
            friend vec4& operator/(vec4& left, const vec4& right);

            vec4& operator+=(const vec4& other);
            vec4& operator-=(const vec4& other);
            vec4& operator*=(const vec4& other);
            vec4& operator/=(const vec4& other);

            bool operator==(const vec4& other);
            bool operator!=(const vec4& other);

            friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
        };

        typedef vec4 Color;
    }
}
#endif //ADUNGL_vec4_H
