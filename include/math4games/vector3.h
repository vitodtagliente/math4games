#pragma once

#include <cmath>
#include <assert.h>

namespace math4games
{
	class tvector3<T>
	{

	public:

		float x, y, z;

		tvector3<T>() {
			x = y = z = 0.0f;
		}

		tvector3<T>(float value) {
			x = y = z = value;
		}

		tvector3<T>(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		tvector3<T>(const tvector3<T>& other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}

		~tvector3<T>() {}

		tvector3<T>& set(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
			return (*this);
		}

		static tvector3<T> zero() {
			return tvector3<T>(0.0f, 0.0f, 0.0f);
		}

		float magnitude() const {
			return sqrt(x*x + y*y + z*z);
		}

		tvector3<T>& normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		float distance(const tvector3<T>& v) const {
			return (*this - v).magnitude();
		}

		static float distance(const tvector3<T>& v1, const tvector3<T>& v2) {
			return (v1 - v2).magnitude();
		}

		float dot(const tvector3<T>& v) const {
			return (*this)*v;
		}

		static float dot(const tvector3<T>& v1, const tvector3<T>& v2) {
			return v1*v2;
		}

		/* cross product */
		tvector3<T> cross(const tvector3<T>& v) const {
			return tvector3<T>(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		static tvector3<T> cross(const tvector3<T>& v1, const tvector3<T>& v2) {
			return tvector3<T>(
				v1.y*v2.z - v1.z*v2.y,
				v1.z*v2.x - v1.x*v2.z,
				v1.x*v2.y - v1.y*v2.x
			);
		}

		/* scalar triple product */
		float triple(const tvector3<T>& v1, const tvector3<T>& v2) const {
			return ((*this).cross(v1))*v2;
		}

		/* scalar triple product */
		static float triple(const tvector3<T>& v1, const tvector3<T>& v2, const tvector3<T>& v3) {
			return (v1.cross(v2))*v3;
		}

		tvector3<T> project(const tvector3<T>& v) {
			return v* ((*this*v) / (v*v));
		}

		static tvector3<T> project(const tvector3<T>& v1, const tvector3<T>& v2) {
			return v2* ((v1*v2) / (v2*v2));
		}

		tvector3<T> reject(const tvector3<T>& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static tvector3<T> reject(const tvector3<T>& v1, const tvector3<T>& v2) {
			return (v1 - v2)* ((v1*v2) / (v2*v2));
		}

		/* Operators overloading */

		float& operator[](int i) {
			return ((&x)[i]);
		}

		const float operator[](int i) const {
			if (i >= 3)
				return 0.0f;
			return ((&x)[i]);
		}

		tvector3<T>& operator=(const tvector3<T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		tvector3<T>& operator+=(const tvector3<T>& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		tvector3<T>& operator-=(const tvector3<T>& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		tvector3<T>& operator*=(const float s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		tvector3<T>& operator/=(const float s) {
			float f = 1.0f / s;
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		bool operator==(const tvector3<T>& other) const {
			return x == other.x &&
				y == other.y && z == other.z;
		}

		bool operator!=(const tvector3<T>& other) const {
			return !(*this == other);
		}

		tvector3<T> operator-() const {
			return tvector3<T>(-x, -y, -z);
		}

		tvector3<T> operator+(const tvector3<T>& v) const {
			return tvector3<T>(x + v.x, y + v.y, z + v.z);
		}

		tvector3<T> operator-(const tvector3<T>& v) const {
			return tvector3<T>(x - v.x, y - v.y, z - v.z);
		}

		tvector3<T> operator*(const float s) const {
			return tvector3<T>(x * s, y * s, z * s);
		}

		tvector3<T> operator/(const float s) const {
			float f = 1.0f / s;
			return tvector3<T>(x * f, y * f, z * f);
		}

		/* dot product */
		float operator*(const tvector3<T>& v) const {
			return (x*v.x + y*v.y + z*v.z);
		}

	};

	inline tvector3<T> operator*(const float s, const tvector3<T>& v) {
		return tvector3<T>(v.x * s, v.y * s, v.z * s);
	}
};