#pragma once

#include "vector2.h"

namespace math4games
{
	class matrix2
	{
	private:
		float m[2][2];

	public:

		matrix2() {
			m[0][0] = m[0][1] = 0.0f;
			m[1][0] = m[1][1] = 0.0f;
		}

		matrix2(float a00, float a01, 
			float a10, float a11) {
			m[0][0] = a00; m[0][1] = a01;
			m[1][0] = a10; m[1][1] = a11;
		}

		matrix2(const vector2& v1, const vector2& v2) {
			m[0][0] = v1.x; m[0][1] = v1.y;
			m[1][0] = v2.x; m[1][1] = v2.y;
		}

		matrix2& set(float a00, float a01,
			float a10, float a11) {
			m[0][0] = a00; m[0][1] = a01;
			m[1][0] = a10; m[1][1] = a11;
			return (*this);
		}

		matrix2& set(const vector2& v1, const vector2& v2) {
			m[0][0] = v1.x; m[0][1] = v1.y;
			m[1][0] = v2.x; m[1][1] = v2.y;
			return (*this);
		}

		vector2 row(int j) const {
			return vector2(m[j][0], m[j][1]);
		}

		vector2 column(int i) const {
			return vector2(m[0][i], m[1][i]);
		}

		static matrix2 zero() {
			return matrix2(
				0.0f, 0.0f,
				0.0f, 0.0f
			);
		}

		static matrix2 identity() {
			return matrix2(
				1.0f, 0.0f,
				0.0f, 1.0f
			);
		}

		matrix2 transpose() {
			return matrix2(
				m[0][0], m[1][0],
				m[0][1], m[1][1]
			);
		}

		static matrix2 inverse(const matrix2& m, bool& invertible) {
			float d = m.determinant();
			if (d != 0.0f) {
				invertible = true;
				return (m.adjugate()) * (1.0f / d);
			}
			invertible = false;
			return m;
		}

		matrix2 adjugate() const {
			return matrix2(
				m[1][1], -m[0][1],
				-m[1][0], m[0][0]
			);
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

		matrix2& operator=(const matrix2& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			m[0][0] = other(0, 0);
			m[0][1] = other(1, 0);
			m[1][0] = other(0, 1);
			m[1][1] = other(1, 1);
 			return *this;
		}

		matrix2& operator+=(const matrix2& other) {
			m[0][0] += other(0, 0);
			m[0][1] += other(1, 0);
			m[1][0] += other(0, 1);
			m[1][1] += other(1, 1);
			return *this;
		}

		matrix2& operator-=(const matrix2& other) {
			m[0][0] -= other(0, 0);
			m[0][1] -= other(1, 0);
			m[1][0] -= other(0, 1);
			m[1][1] -= other(1, 1);
			return *this;
		}

		matrix2& operator*=(float s) {
			m[0][0] *= s;
			m[0][1] *= s;
			m[1][0] *= s;
			m[1][1] *= s;
			return *this;
		}

		matrix2& operator/=(float s) {
			s = 1.0f / s;
			m[0][0] *= s;
			m[0][1] *= s;
			m[1][0] *= s;
			m[1][1] *= s;
			return *this;
		}

		bool operator==(const matrix2& other) const {
			return m[0][0] == other(0, 0) &&
				m[0][1] == other(1, 0) &&
				m[1][0] == other(0, 1) &&
				m[1][1] == other(1, 1);
		}

		bool operator!=(const matrix2& other) const {
			return !(*this == other);
		}

		matrix2 operator-() const {
			return matrix2(
				-m[0][0], -m[0][1],
				-m[1][0], -m[1][1]
			);
		}

		matrix2 operator+(const matrix2& other) const {
			return matrix2(
				m[0][0] + other(0, 0), m[0][1] + other(1, 0),
				m[1][0] + other(0, 1), m[1][1] + other(1, 1)
			);
		}

		matrix2 operator-(const matrix2& other) const {
			return matrix2(
				m[0][0] - other(0, 0), m[0][1] - other(1, 0),
				m[1][0] - other(0, 1), m[1][1] - other(1, 1)
			);
		}

		matrix2 operator*(const float s) const {
			return matrix2(
				m[0][0] * s, m[0][1] * s,
				m[1][0] * s, m[1][1] * s
			);
		}

		matrix2 operator/(const float s) const {
			float f = 1.0f / s;
			return matrix2(
				m[0][0] * f, m[0][1] * f,
				m[1][0] * f, m[1][1] * f
			);
		}

		matrix2 operator*(const matrix2& n) const {
			return matrix2(
				m[0][0] * n(0, 0) + m[0][1] * n(0, 1), m[0][0] * n(1, 0) + m[0][1] * n(1, 1),
				m[1][0] * n(0, 0) + m[1][1] * n(0, 1), m[1][0] * n(1, 0) + m[1][1] * n(1, 1)
			);
		}

		vector2 operator*(const vector2& v) const {
			return vector2(
				m[0][0] * v[0] + m[0][1] * v[1],
				m[1][0] * v[0] + m[1][1] * v[1]
			);
		}
	};

	inline matrix2 operator*(const float s, const matrix2& m) {
		return matrix2(
			m(0, 0) * s, m(1, 0) * s,
			m(0, 1) * s, m(1, 1) * s
		);
	}

	inline vector2 operator*(const vector2& v, const matrix2& m) {
		return vector2(
			v[0] * m(0, 0) + v[1] * m(0, 1),
			v[0] * m(1, 0) + v[1] * m(1, 1)
		);
	}
};