#pragma once

#include "vector3.h"

namespace math4games
{
	class matrix3
	{
	private:
		float m[3][3];

	public:

		matrix3() {
			m[0][0] = m[0][1] = m[0][2] = 0.0f;
			m[1][0] = m[1][1] = m[1][2] = 0.0f;
			m[2][0] = m[2][1] = m[2][2] = 0.0f;
		}

		matrix3(
			float a00, float a10, float a20,
			float a01, float a11, float a21,
			float a02, float a12, float a22
		) {
			m[0][0] = a00; m[0][1] = a10; m[0][2] = a20;
			m[1][0] = a01; m[1][1] = a11; m[1][2] = a21;
			m[2][0] = a02; m[2][1] = a12; m[2][2] = a22;
		}

		matrix3(const vector3& v1, const vector3& v2, const vector3& v3) {
			m[0][0] = v1[0]; m[0][1] = v1[1]; m[0][2] = v1[2];
			m[1][0] = v2[0]; m[1][1] = v2[1]; m[1][2] = v2[2];
			m[2][0] = v3[0]; m[2][1] = v3[1]; m[2][2] = v3[2];
		}

		matrix3& set(
			float a00, float a10, float a20,
			float a01, float a11, float a21,
			float a02, float a12, float a22
		) {
			m[0][0] = a00; m[0][1] = a10; m[0][2] = a20;
			m[1][0] = a01; m[1][1] = a11; m[1][2] = a21;
			m[2][0] = a02; m[2][1] = a12; m[2][2] = a22;
			return (*this);
		}

		matrix3& set(const vector3& v1, const vector3& v2, const vector3& v3) {
			m[0][0] = v1[0]; m[0][1] = v1[1]; m[0][2] = v1[2];
			m[1][0] = v2[0]; m[1][1] = v2[1]; m[1][2] = v2[2];
			m[2][0] = v3[0]; m[2][1] = v3[1]; m[2][2] = v3[2];
			return (*this);
		}

		vector3 row(int j) const {
			return vector3(m[j][0], m[j][1], m[j][2]);
		}

		vector3 column(int i) const {
			return vector3(m[0][i], m[1][i], m[2][i]);
		}

		static matrix3 zero() {
			return matrix3(
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f
			);
		}

		static matrix3 identity() {
			return matrix3(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			);
		}

		matrix3 transpose() {
			return matrix3(
				m[0][0], m[1][0], m[2][0],
				m[0][1], m[1][1], m[2][1],
				m[0][2], m[1][2], m[2][2]
			);
		}

		static matrix3 inverse(const matrix3& m, bool& invertible) {
			float d = m.determinant();
			if (d != 0.0f) {
				invertible = true;
				return (m.adjugate()) * (1.0f / d);
			}
			invertible = false;
			return m;
		}

		matrix3 adjugate() const {
			return (*this); // TODO
		}

		float determinant() const {
			return m[0][0] * m[1][1] - (m[0][1] * m[1][0]);
		}

		/* Operators overloading */

		float& operator()(int i, int j) {
			return (m[j][i]);
		}

		const float& operator()(int i, int j) const {
			return (m[j][i]);
		}

		matrix3& operator=(const matrix3& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			m[0][0] = other(0, 0);
			m[0][1] = other(1, 0);
			m[0][2] = other(2, 0);
			m[1][0] = other(0, 1);
			m[1][1] = other(1, 1);
			m[1][2] = other(2, 1);
			m[2][0] = other(0, 2);
			m[2][1] = other(1, 2);
			m[2][2] = other(2, 2);
			return *this;
		}

		matrix3& operator+=(const matrix3& other) {
			m[0][0] += other(0, 0);
			m[0][1] += other(1, 0);
			m[0][2] += other(2, 0);
			m[1][0] += other(0, 1);
			m[1][1] += other(1, 1);
			m[1][2] += other(2, 1);
			m[2][0] += other(0, 2);
			m[2][1] += other(1, 2);
			m[2][2] += other(2, 2);
			return *this;
		}

		matrix3& operator-=(const matrix3& other) {
			m[0][0] -= other(0, 0);
			m[0][1] -= other(1, 0);
			m[0][2] -= other(2, 0);
			m[1][0] -= other(0, 1);
			m[1][1] -= other(1, 1);
			m[1][2] -= other(2, 1);
			m[2][0] -= other(0, 2);
			m[2][1] -= other(1, 2);
			m[2][2] -= other(2, 2);
			return *this;
		}

		matrix3& operator*=(const float s) {
			m[0][0] *= s;
			m[0][1] *= s;
			m[0][2] *= s;
			m[1][0] *= s;
			m[1][1] *= s;
			m[1][2] *= s;
			m[2][0] *= s;
			m[2][1] *= s;
			m[2][2] *= s;
			return *this;
		}

		matrix3& operator/=(const float s) {
			float d = 1.0f / s;
			m[0][0] *= d;
			m[0][1] *= d;
			m[0][2] *= d;
			m[1][0] *= d;
			m[1][1] *= d;
			m[1][2] *= d;
			m[2][0] *= d;
			m[2][1] *= d;
			m[2][2] *= d;
			return *this;
		}

		bool operator==(const matrix3& other) const {
			return m[0][0] == other(0, 0) && m[0][1] == other(1, 0) && m[0][2] == other(2, 0) &&
				m[1][0] == other(0, 1) && m[1][1] == other(1, 1) && m[1][2] == other(2, 1) &&
				m[2][0] == other(0, 2) && m[2][1] == other(1, 2) && m[2][2] == other(2, 2);
		}

		bool operator!=(const matrix3& other) const {
			return !(*this == other);
		}

		matrix3 operator-() const {
			return matrix3(
				-m[0][0], -m[0][1], -m[0][2],
				-m[1][0], -m[1][1], -m[1][2],
				-m[2][0], -m[2][1], -m[2][2]
			);
		}

		matrix3 operator+(const matrix3& other) const {
			return matrix3(
				m[0][0] + other(0, 0), m[0][1] + other(1, 0), m[0][2] + other(2, 0),
				m[1][0] + other(0, 1), m[1][1] + other(1, 1), m[1][2] + other(2, 1),
				m[2][0] + other(0, 2), m[2][1] + other(1, 2), m[2][2] + other(2, 2)
			);
		}

		matrix3 operator-(const matrix3& other) const {
			return matrix3(
				m[0][0] - other(0, 0), m[0][1] - other(1, 0), m[0][2] - other(2, 0),
				m[1][0] - other(0, 1), m[1][1] - other(1, 1), m[1][2] - other(2, 1),
				m[2][0] - other(0, 2), m[2][1] - other(1, 2), m[2][2] - other(2, 2)
			);
		}

		matrix3 operator*(const float s) const {
			return matrix3(
				m[0][0] * s, m[0][1] * s, m[0][2] * s,
				m[1][0] * s, m[1][1] * s, m[1][2] * s,
				m[2][0] * s, m[2][1] * s, m[2][2] * s
			);
		}

		matrix3 operator/(const float s) const {
			float f = 1.0f / s;
			return matrix3(
				m[0][0] * f, m[0][1] * f, m[0][2] * f,
				m[1][0] * f, m[1][1] * f, m[1][2] * f,
				m[2][0] * f, m[2][1] * f, m[2][2] * f
			);
		}

		matrix3 operator*(const matrix3& n) const {
			return matrix3(
				m[0][0] * n(0, 0) + m[0][1] * n(0, 1) + m[0][2] * n(0, 2),
				m[0][0] * n(1, 0) + m[0][1] * n(1, 1) + m[0][2] * n(1, 2),
				m[0][0] * n(2, 0) + m[0][1] * n(2, 1) + m[0][2] * n(2, 2),
				m[1][0] * n(0, 0) + m[1][1] * n(0, 1) + m[1][2] * n(0, 2),
				m[1][0] * n(1, 0) + m[1][1] * n(1, 1) + m[1][2] * n(1, 2),
				m[1][0] * n(2, 0) + m[1][1] * n(2, 1) + m[2][2] * n(2, 2),
				m[2][0] * n(0, 0) + m[2][1] * n(0, 1) + m[3][2] * n(0, 2),
				m[2][0] * n(1, 0) + m[2][1] * n(1, 1) + m[3][2] * n(1, 2),
				m[2][0] * n(2, 0) + m[2][1] * n(2, 1) + m[3][2] * n(2, 2)
			);
		}
		
		vector3 operator*(const vector3& v) const {
			return vector3(
				m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
				m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
				m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]
			);
		}
		
	};

	inline matrix3 operator*(const float s, const matrix3& m) {
		return matrix3(
			m(0, 0) * s, m(1, 0) * s, m(2, 0) * s,
			m(0, 1) * s, m(1, 1) * s, m(2, 1) * s,
			m(0, 2) * s, m(1, 2) * s, m(2, 2) * s
		);
	}

	inline vector3 operator*(const vector2& v, const matrix3& m) {
		return vector3(
			v[0] * m(0, 0) + v[1] * m(0, 1) + v[2] * m(0, 2),
			v[0] * m(1, 0) + v[1] * m(1, 1) + v[2] * m(1, 2),
			v[0] * m(2, 0) + v[1] * m(2, 1) + v[2] * m(2, 2)
		);
	}
};