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

		vector3& set(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
			return (*this);
		}

		float magnitude() const {
			return sqrt(x*x + y*y + z*z);
		}

		vector3& normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		float distance(const vector3& v) const {
			return (*this - v).magnitude();
		}

		static float distance(const vector3& v1, const vector3& v2) {
			return (v1 - v2).magnitude();
		}

		float dot(const vector3& v) const {
			return (*this)*v;
		}

		static float dot(const vector3& v1, const vector3& v2) {
			return v1*v2;
		}

		/* cross product */
		vector3 cross(const vector3& v) const {
			return vector3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		static vector3 cross(const vector3& v1, const vector3& v2) {
			return vector3(
				v1.y*v2.z - v1.z*v2.y,
				v1.z*v2.x - v1.x*v2.z,
				v1.x*v2.y - v1.y*v2.x
			);
		}

		/* scalar triple product */
		float triple(const vector3& v1, const vector3& v2) const {
			return ((*this).cross(v1))*v2;
		}

		/* scalar triple product */
		static float triple(const vector3& v1, const vector3& v2, const vector3& v3) {
			return (v1.cross(v2))*v3;
		}

		vector3 project(const vector3& v) {
			return v* ((*this*v) / (v*v));
		}

		static vector3 project(const vector3& v1, const vector3& v2) {
			return v2* ((v1*v2) / (v2*v2));
		}

		vector3 reject(const vector3& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static vector3 reject(const vector3& v1, const vector3& v2) {
			return (v1 - v2)* ((v1*v2) / (v2*v2));
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

		vector3& operator-=(const vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vector3& operator*=(float s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		vector3& operator/=(float s) {
			s = 1.0f / s;
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		bool operator==(const vector3& other) const {
			return x == other.x &&
				y == other.y && z == other.z;
		}

		bool operator!=(const vector3& other) const {
			return !(*this == other);
		}

		vector3 operator-() const {
			return vector3(-x, -y, -z);
		}

		vector3 operator+(const vector3& v) const {
			return vector3(x + v.x, y + v.y, z + v.z);
		}

		vector3 operator-(const vector3& v) const {
			return vector3(x - v.x, y - v.y, z - v.z);
		}

		vector3 operator*(float s) const {
			return vector3(x * s, y * s, z * s);
		}

		vector3 operator/(float s) const {
			float f = 1.0f / s;
			return vector3(x * f, y * f, z * f);
		}

		/* dot product */
		float operator*(const vector3& v) const {
			return (x*v.x + y*v.y + z*v.z);
		}

	};

	inline vector3 operator*(float s, const vector3& v) {
		return vector3(v.x * s, v.y * s, v.z * s);
	}
};