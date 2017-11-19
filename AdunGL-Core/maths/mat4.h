//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_mat4_H
#define ADUNGL_mat4_H

#include <cmath>
#include "math_func.h"
#include "vec3.h"
#include "vec4.h"

namespace AdunGL
{
    namespace maths
    {
        struct mat4
        {
            union
            {
                float elements[4 * 4];
                vec4 columns[4];
            };

            mat4();
            mat4(float diagonal);

            vec4 getColumn(int index)
            {
                index *= 4;
                return vec4(elements[index + 0], elements[index + 1], elements[index + 2], elements[index + 3]);
                // return vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
            }

            mat4& multiply(const mat4& other);
            friend mat4& operator*(mat4 left, const mat4& right);
            mat4& operator*=(const mat4& other);

            vec3 multiply(const vec3& other) const;
            friend vec3 operator*(const mat4& left, const vec3& right);

            vec4 multiply(const vec4& other) const;
            friend vec4 operator*(const mat4& left, const vec4& right);

            static mat4 identity();

            static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
            static mat4 perspective(float fov, float aspectRatio, float near, float far);

            static mat4 translation(const vec3& translation);
            static mat4 rotation(float angle, const vec3& axis);
            static mat4 scale(const vec3& scale);
        };
    }
}
#endif //ADUNGL_mat4_H
