//
// Created by adun on 2017. 10. 29..
//

#include "vec2.h"

namespace AdunGL
{
	namespace maths
	{
		vec2::vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		vec2::vec2(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}

		vec2::vec2(const vec3& vector)
		{
			this->x = vector.x;
			this->y = vector.y;
		}

		vec2& vec2::add(const vec2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2& vec2::subtract(const vec2 &other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::multiply(const vec2 &other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2& vec2::divide(const vec2 &other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		vec2 operator+(vec2 left, const vec2& right)
		{
			return left.add(right);
		}

		vec2 operator-(vec2 left, const vec2& right)
		{
			return left.subtract(right);
		}

		vec2 operator*(vec2 left, const vec2& right)
		{
			return left.multiply(right);
		}

		vec2 operator/(vec2 left, const vec2& right)
		{
			return left.divide(right);
		}

		vec2 operator+(vec2 left, float value)
		{
			return vec2(left.x + value, left.y + value);
		}

		vec2 operator*(vec2 left, float value)
		{
			return vec2(left.x * value, left.y * value);
		}

		vec2& vec2::operator+=(const vec2& other)
		{
			return add(other);
		}

		vec2& vec2::operator-=(const vec2& other)
		{
			return subtract(other);
		}

		vec2& vec2::operator*=(const vec2& other)
		{
			return multiply(other);
		}

		vec2& vec2::operator/=(const vec2& other)
		{
			return divide(other);
		}

		bool vec2::operator==(const vec2& other)
		{
			return x == other.x && y == other.y;
		}

		bool vec2::operator!=(const vec2& other)
		{
			return !(*this == other);
		}

		float vec2::magnitude()                 const // ũ��
		{
			return (float)sqrt(x * x + y * y);
		}

		vec2  vec2::normalize()                 const // ����ȭ
		{
			float length = magnitude();

			return vec2(x / length, y / length);
		}

		float vec2::distance(const vec2& other) const // �Ÿ�
		{
			float dist_x = x - other.x;
			float dist_y = y - other.y;

			return (float)sqrt(dist_x * dist_x + dist_y * dist_y);
		}

		float vec2::dot(const vec2& other)      const // ����
		{
			return x * other.x + y * other.y;
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vector)
		{
			stream << "vec2:(" << vector.x << ", " << vector.y << ")";

			return stream;
		}

	}
}