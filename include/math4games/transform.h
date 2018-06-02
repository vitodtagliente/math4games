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
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> transform(const base_vector<N, T>& position,
		const base_vector<N, T>& rotation, const base_vector<N, T>& scale)
	{
		base_matrix<N + 1, N + 1, T> m = identity<N + 1, T>();
		m = translate<N + 1, T>(m, position);
		if (N > 2) m = rotate_z<N + 1, T>(m, rotation[2]);
		m = rotate_y<N + 1, T>(m, rotation[1]);
		m = rotate_x<N + 1, T>(m, rotation[0]);
		m = math4games::scale<N + 1, T>(m, scale);
		return m;
	}
};