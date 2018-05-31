#pragma once

/*
	Quaternion math representation
	Vito Domenico Tagliente
	math library for games
*/

#include "vector.h"

namespace math4games
{
	struct quaternion
	{
		vector3 v;
		float w;
	};
};