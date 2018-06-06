#pragma once

/*
	Transform
	Vito Domenico Tagliente
	math library for games
*/

#include "matrix.h"
#include "transformation.h"

namespace math4games
{
	/*
	template <typename T>
	base_matrix<4, 4, T> transform(const base_vector<3, T>& position,
		const base_vector<3, T>& rotation, const base_vector<3, T>& scale)
	{
		base_matrix<4, 4, T> m = identity<4, T>();
		m = translate<4, T>(m, position);
		m = rotate<4, T>(m, rotation);
		m = math4games::scale<4, T>(m, scale);
		return m;
	}
	*/
};