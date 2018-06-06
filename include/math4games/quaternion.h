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

		}

		quaternion(const vector3& vector, const float scalar) {
			v.data = vector.data;
			w = scalar;

		}

		quaternion(const float x, const float y, const float z, const float _w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			w = _w;
		}
	};
};