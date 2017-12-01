#pragma once

#include "vector4.h"

namespace math4games
{
	class matrix4
	{
	private:

		float m[4][4];

	public:

		matrix4() {
			m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0;
			m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0;
			m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0;
			m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0;
		}


	};
};