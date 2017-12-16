#pragma once
//
// Created by adun on 2017. 10. 29..
//

#define _USE_MATH_DEFINES
#include <cmath>

namespace AdunGL
{
	namespace maths
	{

		const double PI = 3.14159265358979323846;   // pi
		
		inline float toRadians(float degrees)
		{
			return degrees * (PI / 180.0f);
		}

		const float RADIAN = static_cast<float>(PI / 180);

		inline int sign(float value)
		{
			/* 0 / 양수 / 음수 => 0 / 1 / -1 */
			return (value > 0) - (value < 0);
		}

		inline float toDegrees(float radians)
		{
			return (float)(radians * (180.0f / PI));
		}

		inline float sin(float angle)
		{
			return ::sin(angle);
		}

		inline float cos(float angle)
		{
			return ::cos(angle);
		}

		inline float tan(float angle)
		{
			return ::tan(angle);
		}

		inline float sqrt(float value)
		{
			return ::sqrt(value);
		}

		inline float rsqrt(float value)
		{
			return 1.0f / ::sqrt(value);
		}

		inline float asin(float value)
		{
			return ::asin(value);
		}

		inline float acos(float value)
		{
			return ::acos(value);
		}

		inline float atan(float value)
		{
			return ::atan(value);
		}

		inline float atan2(float y, float x)
		{
			return ::atan2(y, x);
		}
	}
}

