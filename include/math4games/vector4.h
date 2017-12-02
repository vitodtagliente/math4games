#pragma once

#include <cmath>

namespace math4games
{
	class vector4
	{

	public:

		float x, y, z, w;

		vector4() {
			x = y = z = w = 0.0f;
		}

		vector4(float value) {
			x = y = z = w = value;
		}

		vector4(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		vector4(const vector4& other) {
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		~vector4() {}

		vector4& set(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
			return (*this);
		}

		float magnitude() const {
			return sqrt(x*x + y*y + z*z + w*w);
		}

		vector4& normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		float distance(const vector4& v) const {
			return (*this - v).magnitude();
		}

		static float distance(const vector4& v1, const vector4& v2) {
			return (v1 - v2).magnitude();
		}

		float dot(const vector4& v) const {
			return (*this)*v;
		}

		static float dot(const vector4& v1, const vector4& v2) {
			return v1*v2;
		}

		vector4 project(const vector4& v) {
			return v* ((*this*v) / (v*v));
		}

		static vector4 project(const vector4& v1, const vector4& v2) {
			return v2* ((v1*v2) / (v2*v2));
		}

		vector4 reject(const vector4& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static vector4 reject(const vector4& v1, const vector4& v2) {
			return (v1 - v2)* ((v1*v2) / (v2*v2));
		}

		/* Operators overloading */

		vector4& operator=(const vector4& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			return *this;
		}

		vector4& operator+=(const vector4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		vector4& operator-=(const vector4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		vector4& operator*=(float s) {
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		vector4& operator/=(float s) {
			s = 1.0f / s;
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		bool operator==(const vector4& other) const {
			return x == other.x &&
				y == other.y && 
				z == other.z &&
				w == other.w;
		}

		bool operator!=(const vector4& other) const {
			return !(*this == other);
		}

		vector4 operator-() const {
			return vector4(-x, -y, -z, -w);
		}

		vector4 operator+(const vector4& v) const {
			return vector4(x + v.x, y + v.y, z + v.z, w + v.z);
		}

		vector4 operator-(const vector4& v) const {
			return vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		vector4 operator*(float s) const {
			return vector4(x * s, y * s, z * s, w * s);
		}

		vector4 operator/(float s) const {
			float f = 1.0f / s;
			return vector4(x * f, y * f, z * f, w * f);
		}

		/* dot product */
		float operator*(const vector4& v) const {
			return (x*v.x + y*v.y + z*v.z + w*v.w);
		}

	};

	inline vector4 operator*(float s, const vector4& v) {
		return vector4(v.x * s, v.y * s, v.z * s, v.w * s);
	}
};