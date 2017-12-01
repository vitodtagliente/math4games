#pragma once

#include <cmath>

namespace math4games
{
	class vector3
	{

	public:

		float x, y, z;

		vector3() {
			x = y = z = 0.0f;
		}

		vector3(float value) {
			x = y = z = value;
		}

		vector3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		vector3(const vector3& other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}

		~vector3() {}

		float magnitude() {
			return sqrt(x*x + y*y + z*z);
		}

		vector3 normalize() {
			return (*this / magnitude());
		}

		float dot(const vector3& v) {
			return (x*v.x + y*v.y + z*v.z);
		}

		vector3 cross(const vector3& v) {
			return vector3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		float distance(const vector3& v) {
			return ((*this) - v).magnitude();
		}

		static float distance(vector3& v1, vector3& v2) {
			return (v1 - v2).magnitude();
		}

		/* Operators overloading */

		vector3& operator=(const vector3& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		vector3& operator+=(const vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		vector3 operator+(const vector3& other) {
			return vector3(*this) += other;
		}

		vector3& operator-=(const vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vector3 operator-(const vector3& other) {
			return vector3(*this) -= other;
		}

		vector3 operator-() {
			return (*this) * -1;
		}

		vector3& operator*=(float s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		vector3 operator*(float s) {
			return vector3(*this) *= s;
		}

		vector3& operator/=(float s) {
			s = 1.0f / s;
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		vector3 operator/(float s) {
			return vector3(*this) /= s;
		}

		bool operator==(const vector3& other) {
			return x == other.x &&
				y == other.y &&
				z == other.z;
		}

		bool operator!=(const vector3& other) {
			return !(*this == other);
		}

	};
};