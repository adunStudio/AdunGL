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

	}
}

