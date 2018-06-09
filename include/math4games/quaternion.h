#pragma once

/*
	Quaternion math representation
	Vito Domenico Tagliente
	math library for games
*/

#include "vector.h"
#include <cmath>

namespace math4games
{
	struct quaternion
	{
		// vector part
		vector3 v;

		// scalar part
		float w;

		quaternion() {
			w = 0.0f;
		}

		quaternion(const vector3& vector, const float scalar = 0.0f) {
			v.data = vector.data;
			w = scalar;
		}

		quaternion(const float x, const float y, const float z, const float _w = 0.0f) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			w = _w;
		}

		// operator overloading

		quaternion operator- () {
			return quaternion(-v, -w);
		}

		quaternion operator+ (const quaternion& q) const {
			return quaternion(v + q.v, w + q.w);
		}

		quaternion& operator+= (const quaternion& q) {
			v += q.v;
			w += q.w;
			return *this;
		}

		quaternion operator* (const float scalar) const {
			return quaternion(v*scalar, w*scalar);
		}

		quaternion& operator*= (const float scalar) {
			v *= scalar;
			w *= scalar;
			return *this;
		}

		float length() const {
			return std::sqrt(std::powf(w, 2) + std::powf(v.magnitude(), 2));
		}

		quaternion normalize() const {
			const float l = length();
			assert(l != 0.0f);
			return (*this)*(1.0f / l);
		}

		quaternion inverse() const {
			const float l = length();
			assert(l != 0.0f);
			const float f = 1.0f / std::pow(l, 2);
			return quaternion((-v)*f, w*f);
		}

		quaternion operator*(const quaternion& q) {
			return quaternion(
				w*q.v + q.w*v + v.cross(q.v),
				w*q.w - (v*q.v)
			);
		}

		quaternion& operator= (const quaternion& q) {
			// check for self-assignment 
			if (this == &q)
				return *this;

			// copy 
			v = q.v;
			w = q.w;
			return *this;
		}

		bool operator== (const quaternion& q) const {
			return v == q.v && w == q.w;
		}

		bool operator!= (const quaternion& q) const {
			return !(*this == q);
		}

		matrix4 matrix() const {
			matrix4 m = matrix4::identity; // TODO
			return m;
		}
	};

	quaternion operator* (const float scalar, const quaternion& q) {
		return q * scalar;
	}
};