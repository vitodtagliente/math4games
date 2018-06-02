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
	base_matrix<N, N, T> rotate_x(const base_matrix<N, N, T>& m, const float theta) {
		return (m * rotate_x<N, T>(theta));
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_y(const float theta) {
		const float rad = deg2rad(theta);
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
	base_matrix<N, N, T> rotate_y(const base_matrix<N, N, T>& m, const float theta) {
		return (m * rotate_y<N, T>(theta));
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_z(const float theta) {
		const float rad = deg2rad(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = c;
		m(1, 0) = s;
		m(0, 1) = -s;
		m(1, 1) = c;
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_z(const base_matrix<N, N, T>& m, const float theta) {
		return (m * rotate_z<N, T>(theta));
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate(const base_vector<N, T>& v, const T theta) {
		// TODO
	}

	template <typename T>
	base_matrix<3, 3, T> rotate(const base_vector<3, T>& v, const T theta) {
		const float rad = deg2rad(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);
		const float d = 1.0f - c;

		const float x = v[0] * d;
		const float y = v[1] * d;
		const float z = v[2] * d;

		const float axay = x * v[1];
		const float axaz = x * v[2];
		const float ayaz = y * v[2];

		base_matrix<3, 3, T> m;
		m(0, 0) = c + x * v[0];
		m(1, 0) = axay - s * v[2];
		m(2, 0) = axaz + s * v[1];

		m(0, 1) = axay + s * v[2];
		m(1, 1) = c + y * v[1];
		m(2, 1) = ayaz - s * v[0];

		m(0, 2) = axaz - s * v[1];
		m(1, 2) = ayaz + s;

		return m;
	}

	template <typename T>
	base_matrix<3, 3, T>& rotate(base_matrix<3, 3, T>& m, const base_vector<3, T>& v, const float theta) {
		return (m *= rotate<3, T>(v, theta));
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
		for (unsigned int i = 0; i < N - 1; ++i)
			m(i, i) *= v[i];
		return m;
	}


}
