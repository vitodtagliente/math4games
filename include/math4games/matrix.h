#pragma once

#include <cmath>
#include <cassert>
#include <initializer_list>
#include <array>

#include "vector.h"

namespace math4games
{
	/*
		n: num of rows
		m: num of columns
	*/
	template<std::size_t n, std::size_t m, class T>
	struct matrix
	{
		T data[n][m];
		const int rows = n;
		const int columns = m;

		matrix() {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] = {};
		}

		matrix(const std::initializer_list<T> args) {
			assert(args.size() <= m*n);
			int i = 0, j = 0;
			for (auto& it : args)
			{
				data[j][i++] = it;
				if (i >= n) {
					++j;
					i = 0;
				}
			}
		}

		T& operator() (int i, int j) {
			assert(i < n && j < m);
			return data[j][i];
		}

		const T& operator() (int i, int j) const {
			return data[j][i];
		}

		/* Operators overloading */

		matrix<n, m, T>& operator= (const matrix<n, m, T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] = other.data[i][j];
			return *this;
		}

		bool operator== (const matrix<n, m, T>& other) const {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (data[i][j] != other.data[i][j])
						return false;
			return true;
		}

		bool operator!= (const matrix<n, m, T>& other) const {
			return !(*this == other);
		}

		matrix<n, m, T>& operator+= (const matrix<n, m, T>& other) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] += other.data[i][j];
			return *this;
		}

		matrix<n, m, T>& operator-= (const matrix<n, m, T>& other) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] -= other.data[i][j];
			return *this;
		}

		matrix<n, m, T>& operator*= (const T s) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] *= s;
			return *this;
		}

		matrix<n, m, T>& operator/= (const T s) {
			T f = 1.0f / s;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] *= f;
			return *this;
		}

		matrix<n, m, T> operator- () const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = -data[i][j];
			return result;
		}

		matrix<n, m, T> operator+ (const matrix<n, m, T>& other) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] + other.data[i][j];
			return result;
		}

		matrix<n, m, T> operator- (const matrix<n, m, T>& other) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] - other.data[i][j];
			return result;
		}

		matrix<n, m, T> operator* (const T s) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] * s;
			return result;
		}

		matrix<n, m, T> operator/ (const T s) const {
			T f = 1.0f / s;
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] * f;
			return result;
		}
	};

	template<typename T>
	struct tmatrix2 : public matrix<2, 2, T>
	{
		tmatrix2() : matrix<2, 2, T>() {}
		tmatrix2(const std::initializer_list<T> args) : matrix<2, 2, T>(args) {}
	};

	typedef tmatrix2<float> matrix2;
	typedef matrix2 m2;
};