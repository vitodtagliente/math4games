#pragma once

/*
quaternion implementation
credits: Vito Domenico Tagliente

quaternion formal representation -> a + bi + cj + dk
*/

#include "vector.h"

namespace math4games
{
	struct quaternion
	{
		float w, x, y, z;
	};
};