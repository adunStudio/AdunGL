//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_MATRIX4_H
#define ADUNGL_MATRIX4_H

#include <cmath>
#include "math_func.h"
#include "vec3.h"
#include "vec4.h"

namespace AdunGL
{
    namespace maths
    {
        struct Matrix4
        {
            union
            {
                float elements[4 * 4];
                Vec4 rows[4];
            };

            Matrix4();
            Matrix4(float diagonal);

            Vec4 getColumn(int index)
            {
                // row index *= 4;
                // row return Vec4(elements[index + 0], elements[index + 1], elements[index + 2], elements[index + 3]);
                return Vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
            }

            Matrix4& multiply(const Matrix4& other);
            friend Matrix4& operator*(Matrix4 left, const Matrix4& right);
            Matrix4& operator*=(const Matrix4& other);

            static Matrix4 identity();

            static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
            static Matrix4 perspective(float fov, float aspectRatio, float near, float far);

            static Matrix4 translation(const Vec3& translation);
            static Matrix4 rotation(float angle, const Vec3& axis);
            static Matrix4 scale(const Vec3& scale);
        };
    }
}
#endif //ADUNGL_MATRIX4_H
