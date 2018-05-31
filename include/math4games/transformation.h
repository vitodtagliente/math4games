#pragma once

/*
	Transformations
	Vito Domenico Tagliente
	math library for games
*/

#include "vector.h"
#include "matrix.h"

namespace math4games
{
	// identity matrix
	template <std::size_t N, typename T>
	base_matrix<N, N, T> identity() {
		base_matrix<N, N, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = static_cast<T>(1.0);
		return m;
	}

	// translation operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> translate(const base_vector<N, T>& v) {
		base_matrix<N, N, T> m = identity<N, T>();
		for (unsigned int j = 0; j < N; ++j)
			m(N - 1, j) = v[j];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> translate(const base_vector<N - 1, T>& v) {
		base_matrix<N, N, T> m = identity<N, T>();
		for (unsigned int j = 0; j < N - 1; ++j)
			m(N - 1, j) = v[j];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T>& translate(base_matrix<N, N, T>& m, const base_vector<N, T>& v) {
		for (unsigned int j = 0; j < N; ++j)
			m(N - 1, j) += v[j];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T>& translate(base_matrix<N, N, T>& m,  const base_vector<N - 1, T>& v) {
		for (unsigned int j = 0; j < N - 1; ++j)
			m(N - 1, j) += v[j];
		return m;
	}

	// rotate operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_x(const float theta) {
		const float rad = deg2rad(theta);
		base_matrix<N, N, T> m = identity<N, T>();
		m(1, 1) = std::cos(rad);
		m(2, 1) = std::sin(rad);
		m(1, 2) = -std::sin(rad);
		m(2, 2) = std::cos(rad);
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_y(const float theta) {
		const float rad = deg2rad(theta);
		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = std::cos(rad);
		m(2, 0) = -std::sin(rad);
		m(0, 2) = std::sin(rad);
		m(2, 2) = std::cos(rad);
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_z(const float theta) {
		const float rad = deg2rad(theta);
		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = std::cos(rad);
		m(1, 0) = std::sin(rad);
		m(0, 1) = -std::sin(rad);
		m(1, 1) = std::cos(rad);
		return m;
	}

	// scale operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> scale(const base_vector<N, T>& v) {
		base_matrix<N, N, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = v[i];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> scale(const base_vector<N - 1, T>& v) {
		base_matrix<N, N, T> m;
		for (unsigned int i = 0; i < N - 1; ++i)
			m(i, i) = v[i];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T>& scale(base_matrix<N, N, T>& m, const base_vector<N, T>& v) {
		for (unsigned int i = 0; i < N; ++i) 
			m(i, i) *= v[i];
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T>& scale(base_matrix<N, N, T>& m, const base_vector<N - 1, T>& v) {
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) *= v[i];
		return m;
	}


}
