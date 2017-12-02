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

		vector2 row(int j) const {
			return vector2(m[j][0], m[j][1]);
		}

		vector2 column(int i) const {
			return vector2(m[0][i], m[1][i]);
		}

		static matrix2 identity() {
			return matrix2(
				1.0f, 0.0f,
				0.0f, 1.0f
			);
		}

		/* Operators overloading */

		const float& operator()(int i, int j) const {
			return (m[j][i]);
		}

	};
};