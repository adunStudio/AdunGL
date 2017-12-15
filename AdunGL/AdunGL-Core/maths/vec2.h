#pragma once
//
// Created by adun on 2017. 10. 29..
//

#include <iostream>
#include <cmath>
#include "vec3.h"

namespace AdunGL
{
	namespace maths
	{
		struct vec2
		{
			float x, y;

			vec2();
			vec2(const float& x, const float& y);
			vec2(const vec3& vector);

			vec2& add(const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divide(const vec2& other);

			friend vec2 operator+(vec2 left, const vec2& right);
			friend vec2 operator-(vec2 left, const vec2& right);
			friend vec2 operator*(vec2 left, const vec2& right);
			friend vec2 operator/(vec2 left, const vec2& right);

			friend vec2 operator+(vec2 left, float value);
			friend vec2 operator*(vec2 left, float value);

			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			bool operator==(const vec2& other);
			bool operator!=(const vec2& other);

			float magnitude()                 const; // 크기
			vec2  normalize()                 const; // 정규화
			float distance(const vec2& other) const; // 거리
			float dot(const vec2& other)      const; // 내적

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};
	}
}
