#pragma once

#include <cmath>

namespace math4games
{
	class vector2
	{

	public:

		float x, y;

		vector2() {
			x = y = 0.0f;
		}

		vector2(float value) {
			x = y = value;
		}

		vector2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		vector2(const vector2& other) {
			x = other.x;
			y = other.y;
		}

		~vector2() {}

		vector2& set(float _x, float _y) {
			x = _x;
			y = _y;
			return (*this);
		}

		/*
		float magnitude() {
			return sqrt(x*x + y*y);
		}

		vector2 normalize() {
			return (*this / magnitude());
		}

		float dot(const vector2& v) {
			return (x*v.x + y*v.y);
		}

		float distance(const vector2& v) {
			return ((*this) - v).magnitude();
		}

		static float distance(vector2& v1, vector2& v2) {
			return (v1 - v2).magnitude();
		}
		*/

		/* Operators overloading */

		vector2& operator=(const vector2& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			return *this;
		}

		vector2& operator+=(const vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		vector2& operator-=(const vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		vector2& operator*=(float s) {
			x *= s;
			y *= s;
			return *this;
		}

		vector2& operator/=(float s) {
			s = 1.0f / s;
			x *= s;
			y *= s;
			return *this;
		}

		bool operator==(const vector2& other) {
			return x == other.x &&
				y == other.y;
		}

		bool operator!=(const vector2& other) {
			return !(*this == other);
		}

	};

	inline vector2 operator-(const vector2& v) {
		return vector2(-v.x, -v.y);
	}

	inline vector2 operator+(const vector2& v1, const vector2& v2) {
		return vector2(v1.x + v2.x, v1.y + v2.y);
	}

	inline vector2 operator-(const vector2& v1, const vector2& v2) {
		return vector2(v1.x - v2.x, v1.y - v2.y);
	}

	inline vector2 operator*(const vector2& v, float s) {
		return vector2(v.x * s, v.y * s);
	}

	inline vector2 operator*(float s, const vector2& v) {
		return vector2(v.x * s, v.y * s);
	}

	inline vector2 operator/(const vector2& v, float s) {
		float f = 1.0f / s;
		return vector2(v.x * f, v.y * f);
	}

	inline float operator*(const vector2& v1, const vector2& v2) {
		return (v1.x*v2.x + v1.y*v2.y);
	}
};