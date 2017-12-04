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

		static vector2 zero() {
			return vector2(0.0f, 0.0f);
		}

		float magnitude() const {
			return sqrt(x*x + y*y);
		}

		vector2& normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		float distance(const vector2& v) const {
			return (*this - v).magnitude();
		}

		static float distance(const vector2& v1, const vector2& v2) {
			return (v1 - v2).magnitude();
		}

		float dot(const vector2& v) const {
			return (*this)*v;
		}

		static float dot(const vector2& v1, const vector2& v2) {
			return v1*v2;
		}

		vector2 project(const vector2& v) {
			return v* ((*this*v) / (v*v));
		}

		static vector2 project(const vector2& v1, const vector2& v2) {
			return v2* ((v1*v2) / (v2*v2));
		}
		
		vector2 reject(const vector2& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static vector2 reject(const vector2& v1, const vector2& v2) {
			return (v1 - v2)* ((v1*v2) / (v2*v2));
		}
		
		/* Operators overloading */

		float& operator[](int i){
			return ((&x)[i]);
		}

		const float operator[](int i) const {
			if (i >= 2)
				return 0.0f;
			return ((&x)[i]);
		}

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

		vector2& operator*=(const float s) {
			x *= s;
			y *= s;
			return *this;
		}

		vector2& operator/=(const float s) {
			float f = 1.0f / s;
			x *= f;
			y *= f;
			return *this;
		}

		bool operator==(const vector2& other) const {
			return x == other.x &&
				y == other.y;
		}

		bool operator!=(const vector2& other) const {
			return !(*this == other);
		}

		vector2 operator-() const {
			return vector2(-x, -y);
		}

		vector2 operator+(const vector2& v) const {
			return vector2(x + v.x, y + v.y);
		}

		vector2 operator-(const vector2& v) const {
			return vector2(x - v.x, y - v.y);
		}

		vector2 operator*(const float s) const {
			return vector2(x * s, y * s);
		}

		vector2 operator/(const float s) const {
			float f = 1.0f / s;
			return vector2(x * f, y * f);
		}

		/* dot product */
		float operator*(const vector2& v) const {
			return (x*v.x + y*v.y);
		}
		
	};

	inline vector2 operator*(const float s, const vector2& v) {
		return vector2(v.x * s, v.y * s);
	}
};