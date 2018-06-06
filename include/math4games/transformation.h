#pragma once

/*
	Transformations
	Vito Domenico Tagliente
	math library for games
*/

#include "vector.h"
#include "point.h"
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

	// point to vector
	template <std::size_t N, typename T>
	base_vector<N + 1, T> vector(const base_point<N, T>& p) {
		base_vector<N + 1, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = p[i];
		v[N] = static_cast<T>(1.0);
		return v;
	}

	// vector to point
	template <std::size_t N, typename T>
	base_point<N - 1, T> point(const base_vector<N, T>& v) {
		static_assert(N > 1, "invalid N");
		base_point<N - 1, T> p;
		for (unsigned int i = 0; i < N - 1; ++i)
			n[i] = v[i];
		return p;
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
	base_matrix<N + 1, N + 1, T> translate(const base_point<N, T>& p) {
		base_matrix<N + 1, N + 1, T> m = identity<N + 1, T>();
		for (unsigned int j = 0; j < N; ++j)
			m(N, j) = p[j];
		return m;
	}

	template <std::size_t N, typename T>
	void translate(base_matrix<N, N, T>& m, const base_vector<N, T>& v) {
		for (unsigned int j = 0; j < N; ++j)
			m(N - 1, j) += v[j];
	}

	template <std::size_t N, typename T>
	void translate(base_matrix<N + 1, N + 1, T>& m,  const base_point<N, T>& p) {
		for (unsigned int j = 0; j < N; ++j)
			m(N, j) += p[j];
	}

	// rotate operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_x(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(1, 1) = c;
		m(2, 1) = s;
		m(1, 2) = -s;
		m(2, 2) = c;
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_y(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = c;
		m(2, 0) = -s;
		m(0, 2) = s;
		m(2, 2) = c;
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_z(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = c;
		m(1, 0) = s;
		m(0, 1) = -s;
		m(1, 1) = c;
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
	base_matrix<N + 1, N + 1, T> scale(const base_point<N, T>& p) {
		base_matrix<N + 1, N + 1, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = p[i];
		return m;
	}

	template <std::size_t N, typename T>
	void scale(base_matrix<N, N, T>& m, const base_vector<N, T>& v) {
		for (unsigned int i = 0; i < N; ++i) 
			m(i, i) *= v[i];
	}

	template <std::size_t N, typename T>
	void scale(base_matrix<N + 1, N + 1, T>& m, const base_point<N, T>& p) {
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) *= v[i];
	}
}
